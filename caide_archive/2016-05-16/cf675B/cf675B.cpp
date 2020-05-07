#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n, a, b, c, d;
	io >> n >> a >> b >> c >> d;
	ll ans = 0;
	for (int k = 1; k <= n; ++k) {
		int mins = a + b + k + 1;
		int maxs = a + b + k + n;

		{
			int curs = a + c + k;
			int minv = max(1, mins - curs);
			int maxv = min(n, maxs - curs);
			umax(mins, curs + minv);
			umin(maxs, curs + maxv);
		}

		{
			int curs = b + d + k;
			int minv = max(1, mins - curs);
			int maxv = min(n, maxs - curs);
			umax(mins, curs + minv);
			umin(maxs, curs + maxv);
		}

		{
			int curs = d + c + k;
			int minv = max(1, mins - curs);
			int maxv = min(n, maxs - curs);
			umax(mins, curs + minv);
			umin(maxs, curs + maxv);
		}

		if (mins <= maxs) {
			ans += maxs - mins + 1;
		}

	}
	io << ans << endl;
}
