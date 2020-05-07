#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

using Field = std::vector<std::string>;

bool check(const Field& a, const Field& b) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (a[i][j] != '?' && a[i][j] != b[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void dfs(Field& a, int v, int pos) {
	int x = v / 3;
	int y = v % 3;
	a[x][y] = pos + '0';
	for (int dir = 0; dir < 4; ++dir) {
		int nx = x + DX[dir];
		int ny = y + DY[dir];
		if (nx < 0 || nx > 2 || ny < 0 || ny > 2 || a[nx][ny] != '0') {
			continue;
		}
		dfs(a, nx * 3 + ny, pos + 1);
		return;
	}
}

bool go(const Field& a, Field& b, int x, int y) {
	b = Field(3, std::string(3, '0'));
	--x, --y;
	b[1][1] = '1';
	b[x / 3][x % 3] = '2';
	dfs(b, y, 3);
	return check(a, b);
}

void solve(istream& in, ostream& out) {
	Field a(3);
	in >> a;
	Field b;
	if (go(a, b, 4, 7) || go(a, b, 4, 1) || go(a, b, 2, 1) || go(a, b, 2, 3) || go(a, b, 6, 3) || go(a, b, 6, 9) || go(a, b, 8, 7) || go(a, b, 8, 9)) {
		for (const auto& it : b) {
			out << it << endl;
		}
		return;
	}
	else {
		assert(false);
	}

}
