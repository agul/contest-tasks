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

  // namespace std

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

using namespace std;

const int MAXN = 100010;
const int MAXM = 1010;

using Bitset = std::bitset<1024>;

Bitset states[MAXN];
int history[MAXN][MAXM];
int history_ans[MAXN];
int current[MAXM];

void solve(std::istream& in, std::ostream& out) {
	int n, m, q;
	in >> n >> m >> q;
	fill(current, 0);
	fill(history, 0);
	states[0].reset();
	history_ans[0] = 0;
	Bitset mask;
	for (int i : range(m)) {
		mask.set(i);
	}
	int ans = 0;
	for (int step : inclusiveRange(1, q)) {
		int type;
		in >> type;
		if (type == 1) {
			int shelf, pos;
			in >> shelf >> pos;
			--shelf, --pos;
			states[step] = states[current[shelf]];
			if (!states[step][pos]) {
				states[step].set(pos);
				++ans;
				current[shelf] = step;
			}
		}
		else if (type == 2) {
			int shelf, pos;
			in >> shelf >> pos;
			--shelf, --pos;
			states[step] = states[current[shelf]];
			if (states[step][pos]) {
				--ans;
				states[step].reset(pos);
				current[shelf] = step;
			}
		}
		else if (type == 3) {
			int shelf;
			in >> shelf;
			--shelf;
			states[step] = states[current[shelf]];
			ans -= states[step].count();
			states[step].flip();
			states[step] &= mask;
			current[shelf] = step;
			ans += states[step].count();
		}
		else if (type == 4) {
			int pos;
			in >> pos;
			std::copy(history[pos], history[pos] + n, current);
			ans = history_ans[pos];
		}
		else {
			assert(false);
		}
		std::copy(current, current + n, history[step]);
		history_ans[step] = ans;
		out << ans << endl;
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

