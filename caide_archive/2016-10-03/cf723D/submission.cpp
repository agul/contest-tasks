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

static constexpr int DX[8] = { -1, 0, 1, 0, -1, -1, 1, 1 };
static constexpr int DY[8] = { 0, 1, 0, -1, -1, 1, 1, -1 };

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

#define fill(a, x) memset(a, x, sizeof(a))

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#define pii std::pair<int, int>

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

template<typename R>
void sort(R& range) {
	std::sort(range.begin(), range.end());
}

using namespace std;

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

