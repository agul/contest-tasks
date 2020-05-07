#include "Head.h"
#include "Queue.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111;

class Cell {
public:
	Cell() : Cell('*') {}

	Cell(const bool up, const bool right, const bool down, const bool left) {
		set(up, right, down, left);
	}

	Cell(const char ch) {
		if (ch == '+') {
			set(1, 1, 1, 1);
		} else
		if (ch == '-') {
			set(0, 1, 0, 1);
		} else
		if (ch == '|') {
			set(1, 0, 1, 0);
		} else
		if (ch == '^') {
			set(1, 0, 0, 0);
		} else
		if (ch == '>') {
			set(0, 1, 0, 0);
		} else
		if (ch == 'v') {
			set(0, 0, 1, 0);
		} else
		if (ch == '<') {
			set(0, 0, 0, 1);
		} else
		if (ch == 'L') {
			set(1, 1, 1, 0);
		} else
		if (ch == 'R') {
			set(1, 0, 1, 1);
		} else
		if (ch == 'U') {
			set(0, 1, 1, 1);
		} else
		if (ch == 'D') {
			set(1, 1, 0, 1);
		} else
		if (ch == '*') {
			set(0, 0, 0, 0);
		}
		else {
			assert(false);
		}
	}

	bool left() const {
		return left_;
	}

	bool right() const {
		return right_;
	}

	bool up() const {
		return up_;
	}

	bool down() const {
		return down_;
	}

	Cell rotate() const {
		return{ left_, up_, right_, down_ };
	}

private:
	bool up_;
	bool right_;
	bool down_;
	bool left_;

	void set(const bool up, const bool right, const bool down, const bool left) {
		up_ = up;
		right_ = right;
		down_ = down;
		left_ = left;
	}

};

class Point3D {
public:
	Point3D() : Point3D(0, 0, 0) {}
	Point3D(const int x, const int y, const int z) :
		x_(x), y_(y), z_(z) {}
	
	int x() const {
		return x_;
	}

	int y() const {
		return y_;
	}

	int z() const {
		return z_;
	}

private:
	int x_;
	int y_;
	int z_;

};

Queue<Point3D> q(MAXN * MAXN * 4);
Cell field[4][MAXN][MAXN];
int dist[4][MAXN][MAXN];
bool used[4][MAXN][MAXN];
int n, m;

inline bool check_bounds(const int z, const int x, const int y) {
	return x > 0 && x <= n && y > 0 && y <= m && z >= 0 && z < 4;
}

inline void add(const int z, const int x, const int y, const int len) {
	if (check_bounds(z, x, y) && !used[z][x][y]) {
		dist[z][x][y] = len;
		used[z][x][y] = true;
		q.push({ x, y, z });
	}
}

bool connection(const Cell& lhs, const Cell& rhs, const Direction dir) {
	if (dir == Direction::Up) {
		return lhs.up() && rhs.down();
	}
	if (dir == Direction::Right) {
		return lhs.right() && rhs.left();
	}
	if (dir == Direction::Down) {
		return lhs.down() && rhs.up();
	}
	if (dir == Direction::Left) {
		return lhs.left() && rhs.right();
	}
	assert(false);
	return false;
}

void solve(istream& ins, ostream& out) {
	ins >> n >> m;
	for (int i = 1; i <= n; ++i) {
		std::string row;
		ins >> row;
		for (int j = 1; j <= m; ++j) {
			field[0][i][j] = Cell(row[j - 1]);
			for (int k = 1; k < 4; ++k) {
				field[k][i][j] = field[k - 1][i][j].rotate();
			}
		}
	}
	pii start, finish;
	ins >> start.X >> start.Y >> finish.X >> finish.Y;
	fill(dist, INF);
	add(0, start.X, start.Y, 0);
	while (!q.empty()) {
		const auto point = q.pop_front();
		const int len = dist[point.z()][point.x()][point.y()];
		const Cell& cur = field[point.z()][point.x()][point.y()];
		for (int dir = 0; dir < 4; ++dir) {
			const int new_z = point.z();
			const int new_x = point.x() + DX[dir];
			const int new_y = point.y() + DY[dir];
			if (!check_bounds(new_z, new_x, new_y)) {
				continue;
			}
			const Cell& rhs = field[new_z][new_x][new_y];
			if (connection(cur, rhs, static_cast<Direction>(dir))) {
				add(new_z, new_x, new_y, len + 1);
			}
		}
		add((point.z() + 1) & 3, point.x(), point.y(), len + 1);
	}
	int ans = INF;
	for (int i = 0; i < 4; ++i) {
		umin(ans, dist[i][finish.X][finish.Y]);
	}
	out << (ans == INF ? -1 : ans) << endl;
}
