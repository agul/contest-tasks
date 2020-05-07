#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 2222;
const int MAXM = 111111;

int dp[MAXN][MAXN];
char s[MAXM];

void solve(istream& ins, ostream& out) {
	dp[0][0] = 1;
	for (int i = 0; i < MAXN - 1; ++i) {
		for (int j = 0; j < MAXN; ++j) {
			if (j < MAXN - 1) {
				add_mod(dp[i + 1][j + 1], dp[i][j]);
			}
			if (j > 0) {
				add_mod(dp[i + 1][j - 1], dp[i][j]);
			}
		}
	}
	int n, ls;
	io >> n >> ls >> s;
	int min_bal = 0;
	int bal = 0;
	for (int i = 0; i < ls; ++i) {
		bal += (s[i] == '(' ? 1 : -1);
		umin(min_bal, bal);
	}
	int diff = n - ls;
	min_bal = abs(min_bal);
	if (min_bal > diff) {
		io << 0 << endl;
		return;
	}
	int ans = 0;
	for (int i = 0; i <= diff; ++i) {
		for (int j = min_bal; j < MAXN; ++j) {
			ll cur = dp[i][j];
			int cur_bal = j + bal;
			if (cur_bal > diff) {
				continue;
			}
			mul_mod(cur, (ll)dp[diff - i][cur_bal]);
			add_mod(ans, (int)cur);
		}
	}
	io << ans << endl;
}
