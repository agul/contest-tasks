#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	ll a, b, c;
	io >> a >> b >> c;
	ll diff = b - a;
	if (c == 0) {
		if (b == a) {
			io << "YES" << endl;
		}
		else {
			io << "NO" << endl;
		}
		return;
	}
	if (diff % c == 0 && diff / c >= 0) {
		io << "YES" << endl;
	}
	else {
		io << "NO" << endl;
	}
}
