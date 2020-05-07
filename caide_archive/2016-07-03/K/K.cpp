#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

vector<int> cnt;

struct Cmp {
	bool operator()(const int& lhs, const int& rhs) const {
		return cnt[lhs] < cnt[rhs] || (cnt[lhs] == cnt[rhs] && lhs < rhs);
	}
};

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<int> a(2 * n);
	cnt.assign(2 * n, 0);
	in >> a;
	for (auto& it : a) {
		--it;
		++cnt[it];
	}
	set<int, Cmp> vals;
	for (int i : range(2 * n)) {
		vals.insert(i);
	}
	set<int> p, q;
	for (int i : range(n)) {
		p.insert(i);
	}
	for (int j : range(n, 2 * n)) {
		q.insert(j);
	}
	std::vector<int> ans;
	while (!vals.empty()) {
		auto it = vals.begin();
		int x = *it;
		vals.erase(it);
		(x < n ? p : q).erase(x);
		ans.emplace_back(x);
		if (cnt[x] != 0) {
			for (const auto& it : p) {
				ans.emplace_back(it);
			}
			break;
		}


		{
			int to = a[x];
			auto it = vals.find(to);
			if (it != vals.end()) {
				vals.erase(it);
				(to < n ? p : q).erase(to);
				int tto = a[to];
				auto jt = vals.find(tto);
				if (jt != vals.end()) {
					vals.erase(jt);
					--cnt[tto];
					vals.insert(tto);
				}
			}
		}
	}
	for (const auto& it : ans) {
		out << it + 1 << " ";
	}
	out << endl;
}
