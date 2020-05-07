#include "base/header.hpp"
#include "queue.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

using Field = std::vector<std::vector<int>>;

Field get_dist(const Field& a, const int sx, const int sy, const int k) {
	Queue<pii> q(MAXN);
	const int n = a.size();
	const int m = a.front().size();
	auto dist = make_vector<int>(n, m, INF);
	auto add_queue = [&a, &q, &dist, &n, &m](const int x, const int y, const int len) {
		if (x < 0 || y < 0 || x >= n || y >= m || a[x][y] == 1 || !umin(dist[x][y], len)) {
			return;
		}
		q.push({ x, y });
	};
	add_queue(sx, sy, 0);
	while (!q.empty()) {
		const int x = q.front().first;
		const int y = q.front().second;
		q.pop_front();
		const int len = dist[x][y];
		for (int dir = 0; dir < 8; ++dir) {
			for (int mx : inclusiveRange(0, k)) {
				int nx = x + DX[dir] * mx;
				for (int my : inclusiveRange(0, k - mx)) {
					int ny = y + DY[dir] * my;
					add_queue(nx, ny, len + 1);
				}
			}
		}
	}
	return dist;
}

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n, m, x, y;
		in >> n >> m >> x >> y;
		auto a = make_vector<int>(n, m, 0);
		in >> a;
		auto d1 = get_dist(a, 0, 0, x);
		auto d2 = get_dist(a, 0, m - 1, y);
		int ans = INF;
		for (int i : range(n)) {
			for (int j : range(m)) {
				umin(ans, max(d1[i][j], d2[i][j]));
			}
		}
		out << (ans == INF ? -1 : ans) << endl;
	}
}
