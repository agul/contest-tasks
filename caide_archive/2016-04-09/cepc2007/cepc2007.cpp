#include "Head.h"
#include "IO/IO.h"
#include "Queue.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 32;

int n, m;
char s[MAXN][MAXN], f[MAXN][MAXN];

inline void tap(char * s, int index) {
	if (index < 0 || index >= m) {
		return;
	}
	s[index] ^= 1;
}

inline int to_mask(const char * s) {
	int result = 0;
	for (int i = 0; i < m; ++i) {
		result = (result << 1) ^ s[i];
	}
	return result;
}

void output(const int ans) {
	if (ans == INF) {
		io << "Damaged billboard." << endl; 
		return;
	}
	io << "You have to tap " << ans << " tiles." << endl;
}

void solve(istream& ins, ostream& out) {
	for (;;) {
		io >> n >> m;
		if (n == 0 && m == 0) {
			break;
		}
		for (int i = 0; i < n; ++i) {
			io >> s[i];
			for (int j = 0; j < m; ++j) {
				if (s[i][j] == '.') {
					s[i][j] = 0;
				}
				else {
					s[i][j] = 1;
				}
			}
		}
		int ans = INF;
		for (int mask = 0; mask < (1 << m); ++mask) {
			int cnt = 0;
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j) {
					f[i][j] = s[i][j];
				}
			}
			for (int i = 0; i < m; ++i) {
				if (mask & (1 << i)) {
					++cnt;
					for (int dx = -1; dx <= 1; ++dx) {
						tap(f[0], i + dx);
					}
					if (n > 1) {
						tap(f[1], i);
					}
				}
			}
			for (int i = 0; i < n - 1; ++i) {
				for (int j = 0; j < m; ++j) {
					if (f[i][j]) {
						for (int dx = -1; dx <= 1; ++dx) {
							tap(f[i + 1], j + dx);
						}
						if (i < n - 2) {
							tap(f[i + 2], j);
						}
						++cnt;
					}
				}
			}
			int msk = to_mask(f[n - 1]);
			if (msk == 0) {
				umin(ans, cnt);
			}
		}
		output(ans);
	}
}
