#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int a, n;
	io >> n >> a;
	if (!(a & 1)) {
		a = n - a;
	}
	int ans = a / 2 + 1;
	io << ans << endl;
}
