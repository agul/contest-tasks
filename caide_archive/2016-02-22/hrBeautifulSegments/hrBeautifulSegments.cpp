#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 2222;

int pref[MAXN][MAXN];

void solve(istream& ins, ostream& out) {
	int n, q;
	io >> n >> q;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	for (int i = 0; i < n; ++i) {
		pref[i][i] = a[i];
		for (int j = i + 1; j < n; ++j) {
			pref[i][j] = pref[i][j - 1] & a[j];
		}
	}
	for (int _ = 0; _ < q; ++_) {
		int l, r, x;
		io >> l >> r >> x;
		--l, --r;
		int ans = 0;
		for (int i = l; i <= r; ++i) {
			if (pref[i][r] > x) {
				continue;
			}
			int L = i - 1, R = r;
			while (R - L > 1) {
				int md = (L + R) >> 1;
				if (pref[i][md] <= x) {
					R = md;
				}
				else {
					L = md;
				}
			}
			ans += r - R + 1;
		}
		io << ans << endl;
	}
}
