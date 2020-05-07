#include "base/header.hpp"
#include "queue.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111111;

void solve(std::istream& in, std::ostream& out) {
	int n, m, s, c;
	in >> n >> m >> s >> c;
	auto field = make_vector<char>(n, m, 0);
	in >> field;
	auto coins = make_vector<int>(n, m, 0);
	for (int i = 0; i < c; ++i) {
		int x, y;
		in >> x >> y;
		++coins[x - 1][y - 1];
	}
	Queue<pii> q(MAXN);
	auto used = make_vector<bool>(n, m, false);
	auto color = make_vector<int>(n, m, 0);
	std::vector<int> ans;
	int timer = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!used[i][j] && field[i][j] == '.') {
				ans.emplace_back(0);
				q.clear();
				q.push({ i, j });
				used[i][j] = true;
				while (!q.empty()) {
					const auto it = q.pop_front();
					int x = it.first;
					int y = it.second;
					color[x][y] = timer;
					ans[timer] += coins[x][y];
					for (int dir = 0; dir < 4; ++dir) {
						int nx = it.first + DX[dir];
						int ny = it.second + DY[dir];
						if (nx < 0 || ny < 0 || nx >= n || ny >= m || field[nx][ny] == '*' || used[nx][ny]) {
							continue;
						}
						used[nx][ny] = true;
						q.push({ nx, ny });
					}
				}
				++timer;
			}
		}
	}
	for (int i = 0; i < s; ++i) {
		int x, y;
		in >> x >> y;
		const int col = color[x - 1][y - 1];
		const int res = ans[col];
		out << res << endl;
	}
}
