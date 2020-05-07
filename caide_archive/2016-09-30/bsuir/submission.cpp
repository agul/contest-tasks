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
constexpr IntegerRange<T> range(const T from, const T to) {
	return IntegerRange<T>(from, to);
}

template<typename T>
constexpr IntegerRange<T> inclusiveRange(const T to) {
	return IntegerRange<T>(0, to + 1);
}

template<typename T>
constexpr IntegerRange<T> inclusiveRange(const T from, const T to) {
	return IntegerRange<T>(from, to + 1);
}

namespace Random {

	static std::chrono::system_clock::rep GetRandSeed() {
		return std::chrono::system_clock::now().time_since_epoch().count();
	}

	static std::mt19937_64 gen(GetRandSeed());
	static std::uniform_int_distribution<long long> distrib(0, std::numeric_limits<long long>::max());

	template<typename T>
	static T get(T r) {
		return distrib(gen) % r;
	}

	template<typename T>
	static T get(T l, T r) {
		return get(r - l + 1) + l;
	}

}

using namespace std;

const int MAXN = 1111;

static constexpr int N = 10;

int field[MAXN][MAXN];
bool used[MAXN][MAXN];
int n;
double ans;
int cnt;

std::unordered_set<int> nums;

std::set<tuple<int, int, int, int>> memo;

int rect(const int i, const int j, const int lenx, const int leny) {
	auto tp = std::make_tuple(i, j, lenx, leny);
	if (memo.count(tp)) {
		return 0;
	}
	memo.insert(tp);
	nums.clear();
	for (int x : range(i, i + lenx)) {
		for (int y : range(j, j + leny)) {
			const int color = field[x][y];
			nums.insert(color);
		}
	}
	++cnt;
	return nums.size();
}

void process(int lenx, int leny) {
	if (used[lenx][leny]) {
		return;
	}
	used[lenx][leny] = true;
	for (int i : inclusiveRange(n - lenx)) {
		for (int j : inclusiveRange(n - leny)) {
			ans += rect(i, j, lenx, leny);
		}
	}
}

void solve(std::istream& in, std::ostream& out) {
	in >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			in >> field[i][j];
			--field[i][j];
		}
	}
	fill(used, 0);
	ans = 0;
	cnt = 0;

	for (int x : inclusiveRange(1, min(n, N))) {
		for (int y : inclusiveRange(1, min(n, N))) {
			process(x, y);
		}
	}

	for (int iter : range(500)) {
		int lenx = Random::get(1, n);
		int leny = Random::get(1, n);
		int i = Random::get(0, n - lenx);
		int j = Random::get(0, n - leny);
		ans += rect(i, j, lenx, leny);
	}

	for (int x : inclusiveRange(max(1, n - N), n)) {
		for (int y : inclusiveRange(max(1, n - N), n)) {
			process(x, y);
		}
	}

	ans /= cnt;
	out << fixed << setprecision(16) << ans << endl;
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

