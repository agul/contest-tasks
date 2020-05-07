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

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#define uint unsigned int

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

int __;

using namespace std;

int wh[256], cnt, rev[64];
uint table[64][1 << 20];

void add_char(const char ch) {
	wh[ch] = cnt;
	rev[cnt] = ch;
	++cnt;
}

inline uint get(const std::string& s) {
	uint ans = 0;
	const int n = s.length();
	for (int i : range(n)) {
		const char cur = s[n - 1 - i];
		ans ^= table[wh[cur]][i];
	}
	return ans;
}

void solve(std::istream& in, std::ostream& out) {
	cnt = 0;
	for (char ch : inclusiveRange('0', '9')) {
		add_char(ch);
	}
	for (char ch : inclusiveRange('A', 'Z')) {
		add_char(ch);
	}
	for (char ch : inclusiveRange('a', 'z')) {
		add_char(ch);
	}

	for (int i : range(cnt)) {
		uint r = rev[i];

		for (int k : range(1000000)) {
			table[i][k] = r;
			for (int j = 0; j < 8; j++) {
				if ((r & 0x80000000) != 0) {
					r = r << 1 ^ 0x04C11DB7;
				}
				else {
					r <<= 1;
				}
			}
		}
	}

	in >> __;
	for (int _ : range(__)) {
		string s;
		int n;
		in >> n >> s;
		uint cur_val = get(s);
		int m;
		in >> m;
		out << cur_val << endl;
		for (int i : range(m)) {
			int x;
			char to;
			in >> x >> to;
			--x;
			const int pos = n - 1 - x;
			cur_val ^= table[wh[s[x]]][pos];
			s[x] = to;
			cur_val ^= table[wh[s[x]]][pos];
			out << cur_val << endl;
		}
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

