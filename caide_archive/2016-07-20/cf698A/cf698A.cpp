#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111;

int dp[MAXN][4];

const int CF = 1;
const int GYM = 2;

inline bool is_cf(const int x) {
	return x == 1 || x == 3;
}

inline bool is_gym(const int y) {
	return y == 2 || y == 3;
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<int> a(n);
	in >> a;
	fill(dp, INF);
	dp[0][0] = 0;
	for (int i = 0; i < n; ++i) {
		const int day = a[i];
		for (int task = 0; task < 3; ++task) {
			if (task != CF && is_cf(day)) {
				umin(dp[i + 1][CF], dp[i][task]);
			}
			if (task != GYM && is_gym(day)) {
				umin(dp[i + 1][GYM], dp[i][task]);
			}
			umin(dp[i + 1][0], dp[i][task] + 1);
		}
	}
	int ans = INF;
	for (int i = 0; i < 3; ++i) {
		umin(ans, dp[n][i]);
	}
	out << ans << endl;
}
