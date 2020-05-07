#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	ll n, a, b, p, q;
	in >> n >> a >> b >> p >> q;
	ll ans = n / a * p + n / b * q;
	if (p > q) {
		ans -= n / (a * b) * q;
	}
	else {
		ans -= n / (a * b) * p;
	}
	out << ans << endl;
}
