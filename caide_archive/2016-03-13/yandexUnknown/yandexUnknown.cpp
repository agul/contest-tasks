#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n;
	ll l, g;
	io >> n >> l >> g;
	for (int i = 1; i < n; ++i) {
		ll x, y;
		io >> x >> y;
		l = lcm(l, x);
		g = gcd(g, y);
	}
	io << l << " " << g << endl;
}
