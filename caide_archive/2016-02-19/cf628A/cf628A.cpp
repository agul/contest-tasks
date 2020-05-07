#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n, b, p;
	io >> n >> b >> p;
	if (n == 0) {
		io << "0 " << p << endl;
		return;
	}
	int m = n;
	int cnt = 0;
	while (n > 1) {
		int deg = 1;
		for (; deg * 2 <= n; deg *= 2);
		deg >>= 1;
		n -= deg;
		cnt += deg;
	}
	io << cnt * (2 * b + 1) << " " << m * p << endl;
}
