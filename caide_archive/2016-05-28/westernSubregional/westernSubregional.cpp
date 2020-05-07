#include "Head.h"
#include "maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void go(const std::vector<ll>& L, const std::vector<ll>& R, int left, int right, std::vector<ll>& ans, ll cursum) {
	if (left == right) {
		ans.emplace_back(cursum);
		return;
	}
	go(L, R, left + 1, right, ans, cursum + L[left]);
	go(L, R, left + 1, right, ans, cursum + R[left]);
}

void process(const std::vector<ll>& L, const std::vector<ll>& R, int left, int right, std::vector<ll>& ans) {
	go(L, R, left, right, ans, 0);
	if (L == R) {
		ans.emplace_back(0);
	}
}

void solve(istream& in, ostream& out) {
	int n;
	ll total;
	in >> n >> total;
	std::vector<ll> r(n), s(n);
	in >> r >> s;
	ll total_r = accumulate(all(r), 0LL);
	std::vector<ll> L(n), R(n);
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		ll a = total * r[i];
		if (a % total_r == 0) {
			ll val = a / total_r;
			if (val % s[i] == 0) {
				L[i] = R[i] =  val;
				continue;
			}
		}
		double val = static_cast<double>(a) / total_r;
		L[i] = static_cast<ll>(val / s[i]);
		R[i] = L[i] + 1;
		L[i] *= s[i];
		R[i] *= s[i];
	}
	std::vector<ll> sa, sb;
	int md = n / 2;
	process(L, R, 0, n / 2, sa);
	process(L, R, n / 2, n, sb);
	sort(all(sa));
	sort(all(sb), greater<ll>());
	int x = 0;
	int y = 0;
	ll best = 0;
	while (x < sa.size() && y < sb.size()) {
		ll sum = sa[x] + sb[y];
		if (abs(sum - total) < abs(total - best) || abs(sum - total) == abs(total - best) && sum < best) {
			best = sum;
		}
		if (sum < total) {
			++x;
		}
		else {
			++y;
		}
	}
	out << best << endl;
}
