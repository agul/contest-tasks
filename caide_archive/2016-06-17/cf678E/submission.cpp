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

#define ctz(a) __ctz(a)
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

static uint32_t __inline __ctz(uint32_t x) {
	unsigned long r = 0;
	_BitScanForward(&r, x);
	return r;
}
#endif

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
	IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	IntegerIterator<T> begin() const {
		return IntegerIterator<T>(begin_);
	}

	IntegerIterator<T> end() const {
		return IntegerIterator<T>(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

using namespace std;

std::vector<int> get_people(const int mask) {
	std::vector<int> people;
	int tmp_mask = mask;
	while (tmp_mask > 0) {
		const int v = ctz(tmp_mask);
		tmp_mask ^= (1 << v);
		people.emplace_back(v);
	}
	return people;
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<vector<double>> prob(n, vector<double>(n));
	in >> prob;
	vector<vector<double>> dp(1 << n, vector<double>(n));
	for (int i : range(n)) {
		prob[i][i] = 1;
		dp[0][i] = 1;
	}
	for (int mask : range(1 << n)) {
		for (int i : range(n)) {
			if (mask & (1 << i)) {
				continue;
			}
			const int nmask = mask ^ (1 << i);
			if (mask == 0) {
				dp[nmask][i] = 1;
				continue;
			}
			const auto people = get_people(mask);
			const auto vec = get_people(nmask);
			double cur = 0;
			for (const auto& it : people) {
				cur += dp[mask][it] * prob[i][it];
			}
			umax(dp[nmask][i], cur);
			for (const auto& it : people) {
				umax(dp[nmask][it], dp[mask][it] * prob[it][i]);
			}
		}
	}
	out << fixed << setprecision(16) << dp.back().front() << endl;
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

