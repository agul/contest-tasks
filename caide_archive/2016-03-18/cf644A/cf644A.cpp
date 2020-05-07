#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111;

int ans[MAXN][MAXN];

void solve(istream& ins, ostream& out) {
	int n, a, b;
	io >> n >> a >> b;
	if (n > a * b) {
		io << -1 << endl;
		return;
	}
	fill(ans, 0);
	for (int i = 0; i < a && n > 0; ++i) {
		for (int j = 0; j < b && n > 0; ++j, --n) {
			ans[i][j] = n;
		}
	}
	for (int i = 0; i < a; ++i) {
		if (!(b & 1) && (i & 1)) {
			reverse(ans[i], ans[i] + b);
		}
		for (int j = 0; j < b; ++j) {
			io << ans[i][j] << " ";
		}
		io << endl;
	}
}
