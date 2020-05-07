#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;



void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<int> a(n);
	ll xmin = INF, ymin = INF, xmax = 0, ymax = 0;
	for (int i = 0; i < n; ++i) {
		ll x, y;
		io >> x >> y;
		umax(xmax, x);
		umax(ymax, y);
		umin(xmin, x);
		umin(ymin, y);
	}
	out << fixed << setprecision(16) << 2.0 * ((xmax - xmin) + (ymax - ymin)) << endl;
}
