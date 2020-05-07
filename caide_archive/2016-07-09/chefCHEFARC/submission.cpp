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

constexpr const int INF = 0x3f3f3f3f;

constexpr const int DX[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
constexpr const int DY[] = { 0, 1, 0, -1, -1, 1, 1, -1 };

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

template<typename T>
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

#ifdef _MSC_VER

#endif

template<typename T, size_t N>
struct MakeVector {
	template<typename... Args,
		typename R = std::vector<decltype(MakeVector<T, N - 1>::make_vector(std::declval<Args>()...)) >>
		static R make_vector(size_t first, Args... sizes) {
		auto inner = MakeVector<T, N - 1>::make_vector(sizes...);
		return R(first, inner);
	}
};

template<typename T>
struct MakeVector<T, 1> {
	/// caide keep
	template<typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

template<typename T, typename... Args>
auto make_vector(Args... args) -> decltype(MakeVector<T, sizeof...(Args)-1>::make_vector(args...)) {
	return MakeVector<T, sizeof...(Args)-1>::make_vector(args...);
}

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#define pii std::pair<int, int>

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

	constexpr explicit IntegerIterator(const value_type value) : value_(value) {}

	IntegerIterator& operator++() {
		++value_;
		return *this;
	}

	constexpr value_type operator*() const {
		return value_;
	}

	constexpr bool operator ==(const IntegerIterator rhs) const {
		return value_ == rhs.value_;
	}

	constexpr bool operator !=(const IntegerIterator rhs) const {
		return !(*this == rhs);
	}

private:
	value_type value_;

};

template<typename T>
class IntegerRange {
public:
	using const_iterator = IntegerIterator<T>;

	constexpr IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	constexpr const_iterator begin() const {
		return const_iterator(begin_);
	}

	constexpr const_iterator end() const {
		return const_iterator(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
constexpr IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

template<typename T>
constexpr IntegerRange<T> inclusiveRange(const T from, const T to) {
	return IntegerRange<T>(from, to + 1);
}

template<typename T>
class Queue {
public:
	using value_type = T;
	using size_type = size_t;
	using reference = value_type&;
	
	using rvalue = value_type&&;
	using container = std::vector<value_type>;

	Queue(const size_type max_size) : data_(container(max_size)) {
		clear();
	}

	Queue() = delete;

	Queue(const Queue&) = default;
	Queue& operator =(const Queue&) = default;
	Queue(Queue&&) = default;
	Queue& operator =(Queue&&) = default;

	reference front() {
		return data_[head_index_];
	}

	constexpr bool empty() const {
		return head_index_ == tail_index_;
	}

	void clear() {
		head_index_ = 0;
		tail_index_ = 0;
	}

	void push(rvalue value) {
		data_[tail_index_++] = std::move(value);
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

int __;

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

