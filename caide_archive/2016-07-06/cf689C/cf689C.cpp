#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 222222;

inline ll calc(const std::vector<ll>& cubes, const ll max_val) {
	ll cnt = 0;
	for (int i = 2; i < MAXN; ++i) {
		cnt += max_val / cubes[i];
	}
	return cnt;
}

void solve(std::istream& in, std::ostream& out) {
	std::vector<ll> cubes(MAXN);
	for (ll i = 0; i < MAXN; ++i) {
		cubes[i] = i * i * i;
	}
	ll L = 1, R = LINF;
	ll n;
	in >> n;
	while (R - L > 1) {
		const ll md = (L + R) >> 1;
		const ll cnt = calc(cubes, md);
		if (cnt < n) {
			L = md;
		}
		else {
			R = md;
		}
	}
	cerr << R << " " << calc(cubes, R) << endl;
	if (calc(cubes, R) != n) {
		out << -1 << endl;
		return;
	}
	out << R << endl;
}
