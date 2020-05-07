#include "Head.h"
#include "IO.h"

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

const ll MAX[8] = { 63, 100, 177, 372, 1000, 3981, 31622, 1000000 };

ull L, R, x;

void solve(istream& ins, ostream& out) {
	io >> L >> R >> x;
	ull p = 1;
	
	bool any = false;
	for (int i = 0; i < 1000000; ++i) {
		if (p > R) {
			break;
		}
		if (p >= L && p <= R) {
			cout << i << " " << p << endl;
			any = true;
		}
		p *= x;
	}
	if (!any) {
		io << -1;
	}
	io << endl;
}
