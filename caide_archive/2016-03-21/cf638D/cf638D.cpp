#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111;

const int dx[] = { 1, 0, 0 };
const int dy[] = { 0, 1, 0 };
const int dz[] = { 0, 0, 1 };

char a[MAXN][MAXN][MAXN];
int n, m, p;

inline bool working(int x, int y, int z) {
	return x >= 0 && x < n && y >= 0 && y < m && z >= 0 && z < p && a[x][y][z] == '1';
}

void solve(istream& ins, ostream& out) {
	io >> n >> m >> p;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			io >> a[i][j];
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < p; ++k) {
				if (!working(i, j, k)) {
					continue;
				}
				bool critical = false;
				for (int dir = 0; dir < 3; ++dir) {
					critical |= (working(i - dx[dir], j - dy[dir], k - dz[dir]) && working(i + dx[dir], j + dy[dir], k + dz[dir]));
				}
				for (int dir_1 = 0; dir_1 < 3; ++dir_1) {
					for (int dir_2 = 0; dir_2 < 3; ++dir_2) {
						critical |= working(i - dx[dir_1], j - dy[dir_1], k - dz[dir_1]) && working(i + dx[dir_2], j + dy[dir_2], k + dz[dir_2]) && !working(i - dx[dir_1] + dx[dir_2], j - dy[dir_1] + dy[dir_2], k - dz[dir_1] + dz[dir_2]);
					}
				}
				ans += (critical ? 1 : 0);
			}
		}
	}
	io << ans << endl;
}
