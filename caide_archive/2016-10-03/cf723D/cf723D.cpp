#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 55;

int n, m, k;
int field[MAXN][MAXN];
bool used[MAXN][MAXN];

int dfs(const int x, const int y, const int remove) {
	int cnt = 1;
	used[x][y] = true;
	if (remove) {
		field[x][y] = true;
	}
	for (int dir : range(4)) {
		int nx = x + DX[dir];
		int ny = y + DY[dir];
		if (nx < 0 || ny < 0 || nx > n + 1 || ny > m + 1 || used[nx][ny] || field[nx][ny]) {
			continue;
		}
		cnt += dfs(nx, ny, remove);
	}
	return cnt;
}

void solve(std::istream& in, std::ostream& out) {
	in >> n >> m >> k;
	fill(field, 0);
	for (int i : inclusiveRange(1, n)) {
		for (int j : inclusiveRange(1, m)) {
			char ch;
			in >> ch;
			field[i][j] = (ch == '*');
		}
	}
	dfs(0, 0, false);
	vector<pair<int, pii>> lakes;
	for (int i : inclusiveRange(1, n)) {
		for (int j : inclusiveRange(1, m)) {
			if (used[i][j] || field[i][j]) {
				continue;
			}
			int size = dfs(i, j, false);
			lakes.emplace_back(size, pii(i, j));
		}
	}
	sort(lakes);
	const int delete_cnt = lakes.size() - k;
	int ans = 0;
	fill(used, 0);
	for (int i : range(delete_cnt)) {
		ans += lakes[i].first;
		dfs(lakes[i].second.first, lakes[i].second.second, true);
	}
	out << ans << endl;
	for (int i : inclusiveRange(1, n)) {
		for (int j : inclusiveRange(1, m)) {
			out << (field[i][j] ? '*' : '.');
		}
		out << endl;
	}
}
