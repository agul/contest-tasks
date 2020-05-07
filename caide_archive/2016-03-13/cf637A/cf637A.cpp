#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111111;

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<int> a(MAXN, 0);
	int best = 0;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		io >> x;
		++a[x];
		if (umax(best, a[x])) {
			ans = x;
		}
	}
	io << ans << endl;
}
