#include "base/header.hpp"
#include "queue.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 4444444;

using Point = std::pair<char, char>;

struct State {
	vector<Point> robots;
	int step;

	State() : step(0) {}

	int hash() {
		sort(robots.begin() + 1, robots.end());
		int res = 0;
		for (auto& it : robots) {
			res = res * 10 + it.first;
			res = res * 10 + it.second;
		}
		return res;
	}

};

using Field = std::vector<std::string>;

State get_state(const Field& field, int robots) {
	State state;
	for (int k : range(robots)) {
		const char need = k + '1';
		for (int i : range(field.size())) {
			for (int j : range(field.front().size())) {
				if (field[i][j] == need) {
					state.robots.emplace_back(i, j);
					break;
				}
			}
		}
	}
	return state;
}

Point find_x(const Field& field) {
	for (int i : range(field.size())) {
		for (int j : range(field.front().size())) {
			if (field[i][j] == 'X') {
				return Point(i, j);
			}
		}
	}
	assert(false);
	return Point(-1, -1);
}

Queue<State> q(MAXN);
unordered_set<int> used;

void add_queue(State& state) {
	const int hash = state.hash();
	if (used.count(hash)) {
		return;
	}
	used.insert(hash);
	q.push(state);
}

void mark_field(Field& field, const Point& point, bool flag) {
	field[point.first][point.second] = (flag ? 'W' : '.');
}

bool check_robot(const Field& field, const Point& finish, const Point& robot) {
	const int n = field.size();
	const int m = field.front().size();
	for (int dir = 0; dir < 4; ++dir) {
		int x = robot.first;
		int y = robot.second;
		int nx = x + DX[dir];
		int ny = y + DY[dir];
		while (nx >= 0 && ny >= 0 && nx < n && ny < m && field[nx][ny] == '.') {
			x = nx;
			y = ny;
			nx += DX[dir];
			ny += DY[dir];
		}
		if (x == finish.first && y == finish.second) {
			return true;
		}
	}
	return false;
}

void move_robot(const Field& field, const State& state, const int index, const int step) {
	const int n = field.size();
	const int m = field.front().size();
	const Point& robot = state.robots[index];
	for (int dir = 0; dir < 4; ++dir) {
		State new_state = state;
		int x = robot.first;
		int y = robot.second;
		int nx = x + DX[dir];
		int ny = y + DY[dir];
		while (nx >= 0 && ny >= 0 && nx < n && ny < m && field[nx][ny] == '.') {
			x = nx;
			y = ny;
			nx += DX[dir];
			ny += DY[dir];
		}
		new_state.robots[index] = Point(x, y);
		new_state.step = step + 1;
		add_queue(new_state);
	}
}

void solve(std::istream& in, std::ostream& out) {
	int n, w, h, k;
	in >> n >> w >> h >> k;
	Field field(h);
	in >> field;
	auto init = get_state(field, n);
	const Point finish = find_x(field);
	mark_field(field, finish, false);
	used.clear();
	q.clear();
	add_queue(init);
	while (!q.empty()) {
		const State state = q.pop_front();
		const int step = state.step;
		int need = 3330;
		if (State(state).hash() == need) {
			need = 3330;
		}
		if (state.robots.front() == finish) {
			out << step << endl;
			return;
		}
		for (const auto& it : state.robots) {
			mark_field(field, it, true);
		}

		if (step == k - 1) {
			/* if (check_robot(field, finish, state.robots.front())) {
				out << k << endl;
				return;
			} */
		}
		else if (step < k) {
			for (int i : range(state.robots.size())) {
				move_robot(field, state, i, step);
			}
		}

		for (const auto& it : state.robots) {
			mark_field(field, it, false);
		}
	}
	out << "NO SOLUTION" << endl;
}
