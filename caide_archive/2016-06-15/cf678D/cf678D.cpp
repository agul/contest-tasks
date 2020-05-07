#include "base/header.hpp"
#include "mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	ll a, b, n, x;
	in >> a >> b >> n >> x;
	if (a == 1) {
		ModInt<int> ans = n;
		ans *= b;
		ans += x;
		out << ans << endl;
		return;
	}
	ModInt<int> p = a;
	p = binpow(p, n);
	ModInt<int> rev = a - 1;
	rev = rev.inverse();
	ModInt<int> ans = (p - 1) * rev * b + p * x;
	out << ans << endl;
}
