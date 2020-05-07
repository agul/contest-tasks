#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int pref[MAXN][2];
char s[MAXN];

void solve(istream& ins, ostream& out) {
	int ls, k;
	io >> ls >> k >> s;
	for (int i = 0; i < ls; ++i) {
		s[i] -= 'a';
	}
	fill(pref, 0);
	for (int i = 1; i <= ls; ++i) {
		pref[i][0] = pref[i - 1][0];
		pref[i][1] = pref[i - 1][1];
		++pref[i][s[i - 1]];
	}
	int ans = 0;
	for (int i = 1; i <= ls; ++i) {
		for (int j = 0; j < 2; ++j) {
			int L = i, R = ls + 1;
			const int offset = pref[i - 1][j ^ 1];
			while (R - L > 1) {
				const int md = (L + R) >> 1;
				const int to_change = pref[md][j ^ 1] - offset;
				if (to_change <= k) {
					L = md;
				}
				else {
					R = md;
				}
			}
			umax(ans, L - i + 1);
		}
	}
	io << ans << endl;
}
