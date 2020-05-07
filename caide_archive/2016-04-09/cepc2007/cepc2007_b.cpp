#include "Head.h"
#include "IO/IO.h"
#include "Queue.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111;

struct Point {
	int x, y;

	Point() : x(0), y(0) {}

	friend IO& operator >> (IO& io, Point& rhs) {
		io >> rhs.x >> rhs.y;
	}

};

int calc(const std::vector<Point>& a, double x) {

}

void solve(istream& ins, ostream& out) {
	for (;;) {
		int n, m;
		io >> n >> m;
		if (n == 0 && m == 0) {
			break;
		}
		vector<Point> a(n);
		for (auto& it : a) {
			io >> it;
		}
		double Lx = 0, Rx = 1e6;
		for (int iter = 0; iter < 100; ++iter) {
			double diff = (Rx - Lx) / 3, m1 = Lx + diff, m2 = Rx - diff;
			if (calc(a, m1) < calc(a, m2)) {
				Lx = m1;
			}
			else {
				Rx = m2;
			}
		}
		int ans = calc(a, (Lx + Rx) / 2);
		io << "It is possible to cover " << ans << " points." << endl;
	}
}
