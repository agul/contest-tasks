#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 2222;

char a[MAXN], b[MAXN];

int is_good(const int ls, const int n, const int d, char* s) {
	int rem = 0;
	for (int i = 0; i < ls; ++i) {
		if ((i & 1) ^ (dig(s[i]) == d)) {
			return 0;
		}
		rem = (rem * 10 + dig(s[i])) % n;
	}
	return 1;
}

int dp[MAXN][MAXN][2];

int count(const int ls, const int n, const int d, char* s) {
	fill(dp, 0);
	dp[0][0][1] = 1;
	for (int pos = 0; pos < ls; ++pos) {
		int cur_val = dig(s[pos]);
		for (int rem = 0; rem < n; ++rem) {
			for (int eq = 0; eq < 2; ++eq) {
				int cur_dp = dp[pos][rem][eq];
				if (!cur_dp) {
					continue;
				}
				if (pos & 1) {
					int new_rem = rem;
					mul_mod(new_rem, 10, n);
					add_mod(new_rem, d % n, n);
					if (eq && d <= cur_val) {
						add_mod(dp[pos + 1][new_rem][d == cur_val], cur_dp);
					} else
					if (!eq) {
						add_mod(dp[pos + 1][new_rem][0], cur_dp);
					}
					continue;
				}
				for (int dig = 0; dig < 10; ++dig) {
					if (dig == d || (dig == 0 && pos == 0)) {
						continue;
					}
					if (eq && dig > cur_val) {
						break;
					}
					int new_rem = rem;
					mul_mod(new_rem, 10, n);
					add_mod(new_rem, dig % n, n);
					if (eq) {
						add_mod(dp[pos + 1][new_rem][dig == cur_val], cur_dp);
					} else {
						add_mod(dp[pos + 1][new_rem][0], cur_dp);
					}
				}
			}
		}
	}
	int ret = dp[ls][0][0];
	return add_mod(ret, dp[ls][0][1]);
}

void solve(istream& ins, ostream& out) {
	int n, d;
	io >> n >> d >> a >> b;
	int ls = strlen(a);
	int ans = count(ls, n, d, b);
	io << add_mod(sub_mod(ans, count(ls, n, d, a)), is_good(ls, n, d, a)) << endl;
}
