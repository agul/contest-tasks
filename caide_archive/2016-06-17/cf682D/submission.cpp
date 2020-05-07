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

template<typename T>
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

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
IntegerRange<T> inclusiveRange(const T to) {
	return IntegerRange<T>(0, to + 1);
}

using namespace std;

const int MAXN = 1111;

int dp[MAXN][MAXN][16][2];

void solve(std::istream& in, std::ostream& out) {
	int ls, lt, cnt;
	string s, t;
	in >> ls >> lt >> cnt >> s >> t;
	fill(dp, 0);
	for (int i = 0; i < ls; ++i) {
		for (int j = 0; j < lt; ++j) {
			for (int k = 0; k <= 10; ++k) {
				for (int mask = 0; mask < 2; ++mask) {
					const int val = dp[i][j][k][mask];
					if ((mask == 1 && val == 0) || k > val) {
						continue;
					}
					umax(dp[i + 1][j + 1][k][0], val);
					umax(dp[i + 1][j][k][0], val);
					umax(dp[i][j + 1][k][0], val);
					if (s[i] != t[j]) {
						continue;
					}
					umax(dp[i + 1][j + 1][k + 1][1], val + 1);
					if (mask == 1) {
						umax(dp[i + 1][j + 1][k][1], val + 1);
					}
				}
			}
		}
	}
	/* for (int mask = 0; mask < 2; ++mask) {
		for (int k = 1; k <= cnt; ++k) {
			for (int i = 1; i <= ls; ++i) {
				for (int j = 1; j <= lt; ++j) {
					std::cerr << dp[i][j][k][mask] << " ";
				}
				std::cerr << std::endl;
			}
			std::cerr << std::endl << std::endl;
		}
		std::cerr << "===============" << std::endl;
	} */
	int ans = 0;
	for (int i : inclusiveRange(ls)) {
		for (int j : inclusiveRange(lt)) {
			for (int mask : range(2)) {
				umax(ans, dp[i][j][cnt][mask]);
			}
		}
	}
	out << ans << endl;
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

