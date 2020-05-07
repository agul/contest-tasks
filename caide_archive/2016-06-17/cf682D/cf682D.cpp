#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111;

int dp[MAXN][MAXN][16][2];

void solve(std::istream& in, std::ostream& out) {
	int ls, lt, cnt;
	string s, t;
	in >> ls >> lt >> cnt >> s >> t;
	fill(dp, 0);
	for (int i = 0; i < ls; ++i) {
		for (int j = 0; j < lt; ++j) {
			for (int k = 0; k <= 10; ++k) {
				for (int mask = 0; mask < 2; ++mask) {
					const int val = dp[i][j][k][mask];
					if ((mask == 1 && val == 0) || k > val) {
						continue;
					}
					umax(dp[i + 1][j + 1][k][0], val);
					umax(dp[i + 1][j][k][0], val);
					umax(dp[i][j + 1][k][0], val);
					if (s[i] != t[j]) {
						continue;
					}
					umax(dp[i + 1][j + 1][k + 1][1], val + 1);
					if (mask == 1) {
						umax(dp[i + 1][j + 1][k][1], val + 1);
					}
				}
			}
		}
	}
	/* for (int mask = 0; mask < 2; ++mask) {
		for (int k = 1; k <= cnt; ++k) {
			for (int i = 1; i <= ls; ++i) {
				for (int j = 1; j <= lt; ++j) {
					std::cerr << dp[i][j][k][mask] << " ";
				}
				std::cerr << std::endl;
			}
			std::cerr << std::endl << std::endl;
		}
		std::cerr << "===============" << std::endl;
	} */
	int ans = 0;
	for (int i : inclusiveRange(ls)) {
		for (int j : inclusiveRange(lt)) {
			for (int mask : range(2)) {
				umax(ans, dp[i][j][cnt][mask]);
			}
		}
	}
	out << ans << endl;
}
