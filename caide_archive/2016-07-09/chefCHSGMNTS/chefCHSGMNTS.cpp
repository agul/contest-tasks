#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

inline ll get_c(const ll len) {
	return len * (len + 1) / 2;
}

void add_segment(std::set<pii>& segs, ll& ans, const int x, const int y) {
	if (y < x) {
		return;
	}
	segs.emplace(x, y);
	const ll len = y - x + 1;
	ans += get_c(len);
}

void remove_element(std::set<pii>& segs, ll& ans, const int x) {
	auto it = segs.lower_bound({ x, x });
	if (it == segs.cend() || it->first != x) {
		--it;
	}
	const int fs = it->first;
	const int sc = it->second;
	segs.erase(it);
	const int len = sc - fs + 1;
	ans -= get_c(len);
	add_segment(segs, ans, fs, x - 1);
	add_segment(segs, ans, x + 1, sc);
}

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n;
		in >> n;
		std::unordered_map<int, int> comp;
		std::vector<std::vector<int>> pos(n);
		std::vector<int> a;
		for (int i : range(n)) {
			int x;
			in >> x;
			auto it = comp.find(x);
			int val = 0;
			if (it == comp.cend()) {
				val = comp.size();
				comp[x] = val;
			}
			else {
				val = it->second;
			}
			a.emplace_back(val);
			pos[val].emplace_back(i);
		}
		std::unordered_set<int> used;
		std::set<pii> segs;
		ll ans = 0;
		for (int i : range(n)) {
			used.clear();
			segs.clear();
			ll cur_cnt = 0;
			add_segment(segs, cur_cnt, i, n - 1);
			for (int j : range(i, n)) {
				const int val = a[j];
				if (used.count(val)) {
					ans += cur_cnt;
					continue;
				}
				used.emplace(val);
				for (int k : pos[val]) {
					if (k >= j) {
						remove_element(segs, cur_cnt, k);
					}
				}
				ans += cur_cnt;
			}
		}
		out << ans << endl;
	}
}
