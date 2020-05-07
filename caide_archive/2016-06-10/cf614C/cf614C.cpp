#include "Head.h"
#include "IO.h"
#include "Maths.h"

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int n;
ll x, y, xx, yy;

#define PI 3.14159265358979323846

void solve(istream& ins, ostream& out) {
	io >> n >> xx >> yy;
	ll mn = LINF, mx = -LINF;
	for (int i = 0; i < n; ++i) {
		io >> x >> y;
		ll dst = sqr(x - xx) + sqr(y - yy);
		umax(mx, dst);
		umin(mn, dst);
	}
	out << setprecision(17) << PI * (mx - mn) << endl;
}
