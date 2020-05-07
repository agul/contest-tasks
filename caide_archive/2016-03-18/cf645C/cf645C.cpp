#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

char s[MAXN];
int pref[MAXN];

void solve(istream& ins, ostream& out) {
	int n, k;
	io >> n >> k >> s;
	pref[0] = 0;
	for (int i = 0; i < n; ++i) {
		pref[i + 1] = pref[i] + (s[i] == '0' ? 1 : 0);
	}
	int L = 0, R = n;
	while (R - L > 1) {
		int md = (L + R) >> 1;
		bool ok = false;
		for (int i = 1; i <= n && !ok; ++i) {
			int lb = max(1, i - md);
			int rb = min(n, i + md);
			ok |= (s[i - 1] == '0' && pref[rb] - pref[lb - 1] > k);
		}
		(ok ? R : L) = md;
	}
	io << R << endl;
}
