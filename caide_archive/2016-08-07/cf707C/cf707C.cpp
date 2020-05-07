#include "base/header.hpp"
#include "maths/maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	ll n;
	in >> n;
	if ((n & (n - 1)) == 0) {
		if (n < 4) {
			out << -1 << endl;
			return;
		}
		ll mul = n / 4;
		out << mul * 3 << " " << mul * 5 << endl;
		return;
	}
	ll mul = 1;
	while ((n & 1) == 0) {
		mul <<= 1;
		n >>= 1;
	}
	ll k = n / 2;
	out << k * 2 * (k + 1) * mul << " " << (k * 2 * (k + 1) + 1) * mul << endl;
}
