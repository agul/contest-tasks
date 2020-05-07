#include "Head.h"
#include "IO/IO.h"
#include "DSU.h"
#include "Maths.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111;

double x[MAXN], y[MAXN];
DSU dsu(MAXN);

void solve(istream& ins, ostream& out) {
	ins >> __;
	for (int _ = 0; _ < __; ++_) {
		int n;
		ins >> n;
		for (int i = 0; i < n; i++) {
			ins >> x[i] >> y[i];
		}
		x[n] = x[0];
		y[n] = y[0];
		double midx = (x[0] + x[1]) / 2, midy = (y[0] - y[1]) / 2;
		double co = (x[1] - x[0]) / sqrt(sqr(x[1] - x[0]) + sqr(y[1] - y[0])),
			si = -(y[1] - y[0]) / sqrt(sqr(x[1] - x[0]) + sqr(y[1] - y[0]));
		for (int i = 0; i < n; i++)
		{
			x[i] -= midx;
			y[i] -= midy;
		}
		for (int i = 0; i < n; i++)
		{
			double xx = x[i] * co - si * y[i], yy = x[i] * si + co * y[i];
			x[i] -= xx;
			y[i] -= yy;
		}
		double pi4 = 1.0 / sqrt(2.0);
		for (int i = 0; i < n; i++)
		{
			double xx = x[i] * pi4 + pi4 * y[i], yy = -x[i] * pi4 + pi4 * y[i];
			x[i] -= xx;
			y[i] -= yy;
		}
		int index1,x1,y1;
		for (int i = 1; i < n; i++)
			if((x[i]<=0)&&(x[i+1]>=0)){
				index1 = i;
				y1 = 0;
				double p = y[i] / (y[i + 1] - y[i]);
				x1 = x[i] + p*(x[i + 1] - x[i]);
				break;
			}
		for (int i = 0; i < n; i++)
		{
			double xx = -y[i], yy = x[i];
			x[i] -= xx;
			y[i] -= yy;
		}
		out << fixed << setprecision(16) << (L + R) / 2 << endl;
	}
}
