#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	ll n, k, ans;
	io >> n >> k;
	ans = 0;
	umin(k, n / 2);
	for (int i = 1, j = 1; i <= k; ++i, j += 2) {
		ans += (n - j) * 2 - 1;
	}
	io << ans << endl;
}
