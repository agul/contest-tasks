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
class Queue {
public:
	using value_type = T;
	using size_type = size_t;
	
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

