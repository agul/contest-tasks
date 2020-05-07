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
		for (int i = 0; i <= n; i++)
		{
			x[i] -= midx;
			y[i] -= midy;
		}
		midx = 0; midy = 0;
		for (int i = 0; i <= n; i++)
		{
			double xx = x[i] * co - si * y[i], yy = x[i] * si + co * y[i];
			x[i] = xx;
			y[i] = yy;
		}
		double pi4 = 1.0 / sqrt(2.0);
		for (int i = 0; i <= n; i++)
		{
			double xx = x[i] * pi4 + pi4 * y[i], yy = -x[i] * pi4 + pi4 * y[i];
			x[i] = xx;
			y[i] = yy;
		}
		int ind1;
		double x1, y1,eps_1=1.e-9;
		for (int i = 1; i < n; i++)
			if (y[i+1]+eps_1>=0) {
				ind1 = i;
				y1 = 0;
				double p = -y[i] / (y[i + 1] - y[i]);
				x1 = x[i] + p*(x[i + 1] - x[i]);
				break;
			}
		for (int i = 0; i <= n; i++)
		{
			double xx = y[i], yy = -x[i];
			x[i] = xx;
			y[i] = yy;
		}
		double xx = y1, yy = -x1;
		y1 = yy;
		x1 = xx; 
		int ind2;
		double x2, y2;
		for (int i = 1; i < n; i++)
			if (y[i + 1]+eps_1 >= 0) {
				ind2 = i;
				y2 = 0;
				double p = -y[i] / (y[i + 1] - y[i]);
				x2 = x[i] + p*(x[i + 1] - x[i]);
				break;
			}
		double s = 0;
		if (ind1 == ind2) {
			s = abs((x1-midx)*(y1+midy) + (x2-x1)*(y1+y2) + (midx-x2)*(y2+midy))/2.0;
		}
		else
		{
			for (int i = ind1 + 1; i < ind2; i++) {
				s += abs((x[i] - midx)*(y[i] + midy) + (x[i + 1] - x[i])*(y[i] + y[i + 1])
					+ (midx - x[i + 1])*(y[i + 1] + midy)) / 2.0;
			}
			s += abs((x1 - midx)*(y1 + midy) + (x[ind1 + 1] - x1)*(y1 + y[ind1 + 1])
				+ (midx - x[ind1 + 1])*(y[ind1 + 1] + midy)) / 2.0;
			s += abs((x2 - midx)*(y2 + midy) + (x[ind2] - x2)*(y2 + y[ind2])
				+ (midx - x[ind2])*(y[ind2] + midy)) / 2.0;
		}
		double ss = 0;
		for (int i = 0; i < n; i++) {
			ss += abs((x[i] - midx)*(y[i] + midy) + (x[i + 1] - x[i])*(y[i] + y[i + 1])
				+ (midx - x[i + 1])*(y[i + 1] + midy)) / 2.0;
		}
		out << fixed << setprecision(16) << s/ss << endl;
	}
}
