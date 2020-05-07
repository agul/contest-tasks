#pragma comment(linker, "/STACK:66777216")
#pragma warning(disable : 4996)

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#pragma hdrstop

const int DX[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
const int DY[] = { 0, 1, 0, -1, -1, 1, 1, -1 };

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#ifdef _MSC_VER

#endif

template<typename T, size_t N>
struct MakeVector {
	
};

template<typename T>
struct MakeVector<T, 1> {
	/// caide keep
	template<typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

namespace std {

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
	for (auto& it : vec) {
		in >> it;
	}
	return in;
}

}

#include <iterator>

template<typename T>
class IntegerIterator : public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T*, T> {
public:
	using value_type = T;

	explicit IntegerIterator(const value_type value) : value_(value) {}

	IntegerIterator& operator++() {
		++value_;
		return *this;
	}

	value_type operator*() const {
		return value_;
	}

	bool operator ==(IntegerIterator rhs) const {
		return value_ == rhs.value_;
	}

	bool operator !=(IntegerIterator rhs) const {
		return !(*this == rhs);
	}

private:
	value_type value_;

};

template<typename T>
class IntegerRange {
public:
	using const_iterator = IntegerIterator<T>;

	IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	const_iterator begin() const {
		return const_iterator(begin_);
	}

	const_iterator end() const {
		return const_iterator(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

template<typename T>
class Queue {
public:
	using value_type = T;
	using size_type = size_t;
	
	using const_reference = const value_type&;
	
	using container = std::vector<value_type>;

	Queue(const size_type max_size) : data_(container(max_size)) {
		clear();
	}

	Queue() = delete;

	Queue(const Queue&) = default;
	Queue& operator =(const Queue&) = default;
	Queue(Queue&&) = default;
	Queue& operator =(Queue&&) = default;

	constexpr bool empty() const {
		return head_index_ == tail_index_;
	}

	void clear() {
		head_index_ = 0;
		tail_index_ = 0;
	}

	void push(const_reference value) {
		data_[tail_index_++] = value;
	}

	value_type pop_front() {
		return data_[head_index_++];
	}

private:
	container data_;
	size_type head_index_;
	size_type tail_index_;

};

using namespace std;

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

#include <fstream>

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}

