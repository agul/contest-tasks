#include "base/header.hpp"
#include "maths/rational.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

using R = Rational<ll>;

bool cmp(const pii& lhs, const pii& rhs) {
	return lhs.first * rhs.second < rhs.first * lhs.second;
}

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<int> a(n);
	in >> a;
	
	vector<pii> items;
	auto parts = make_vector<pii>(n, k, pii(1, 1));
	for (int i : range(n)) {
		for (int j : range(k)) {
			auto cur_part = pii(a[i], j + 1);
			parts[i][j] = cur_part;
			items.emplace_back(cur_part);
		}
	}
	vector<int> ptr(n, k - 1);
	sort(items, cmp);

	R best = R(items.back().first, items.back().second) / R(items.front().first, items.front().second);
	vector<int> ans(n, 0);
	for (const auto& it : items) {
		bool ok = true;
		pii mx(0, 1);
		for (int i : range(n)) {
			int& x = ptr[i];
			while (x > 0 && cmp(parts[i][x], it)) {
				--x;
			}
			if (x == 0 && cmp(parts[i][0], it)) {
				ok = false;
				break;
			}
			if (cmp(mx, parts[i][x])) {
				mx = parts[i][x];
			}
		}
		if (!ok) {
			break;
		}
		R cur_ratio = R(mx.first, mx.second) / R(it.first, it.second);
		if (umin(best, cur_ratio)) {
			ans = ptr;
		}
	}

	for (const auto& it : ans) {
		out << it + 1 << " ";
	}
	out << endl;
}
