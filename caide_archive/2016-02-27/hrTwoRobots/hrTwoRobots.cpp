#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111;

int dp[MAXN][2][2];
vector<pii> q;
vector<int> pref;

inline int dist(int x, int y) {
	return (x == 0 ? 0 : abs(q[x].Y - q[y].X));
}

void relax(int i, int j, int fs, int sc) {
	if (fs + sc < dp[i][j][0] + dp[i][j][1]) {
		dp[i][j][j] = fs;
		dp[i][j][j ^ 1] = sc;
	}
}

inline int get_pref(int L, int R) {
	if (L >= R) {
		return 0;
	}
	return pref[R] - pref[L];
}

void solve(istream& ins, ostream& out) {
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		int n, m;
		io >> m >> n;
		q.resize(1);
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			int x, y;
			io >> x >> y;
			q.emplace_back(x, y);
			ans += abs(x - y);
		}
		pref = std::move(vector<int>(n + 1, 0));
		for (int i = 2; i <= n; ++i) {
			pref[i] = pref[i - 1] + dist(i - 1, i);
		}
		fill(dp, INF);
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				dp[0][i][j] = 0;
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < i; ++k) {
					relax(i, j, dp[k][j][j] + dist(k, i), dp[k][j][j ^ 1] + get_pref(k + 1, i - 1));
				}
			}
		}
		int cur = INF;
		for (int i = 0; i < 2; ++i) {
			int sum = 0;
			for (int j = 0; j < 2; ++j) {
				sum += dp[n][i][j];
			}
			umin(cur, sum);
		}
		io << ans + cur << endl;
	}
}
