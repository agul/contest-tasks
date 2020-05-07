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

#define ll long long

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

	IntegerIterator& operator--() {
		--value_;
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
class ReversedIntegerRange {
public:
	using const_iterator = IntegerIterator<T>;
	using reverse_iterator = std::reverse_iterator<const_iterator>;

	constexpr ReversedIntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	constexpr reverse_iterator begin() const {
		return reverse_iterator(const_iterator(begin_));
	}

	constexpr reverse_iterator end() const {
		return reverse_iterator(const_iterator(end_));
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
constexpr ReversedIntegerRange<T> downrange(const T from, const T to) {
	return ReversedIntegerRange<T>(from, to);
}

using namespace std;

inline bool is_pow(const int n) {
	return (n & (n - 1)) == 0;
}

inline int get_value(const char ch) {
	return ch == '?' ? 10 : ch - '0';
}

void solve(std::istream& in, std::ostream& out) {
	ll n;
	std::array<bool, 11> vals;
	while (in >> n) {
		if (n == 0) {
			break;
		}
		string s;
		in >> s;
		if (!is_pow(s.length() + 1)) {
			out << -1 << endl;
			continue;
		} 
		if (s.length() == 1) {
			if (s == "?") {
				if (n >= 10) {
					out << -1 << endl;
				}
				else {
					out << n << endl;
				}
			}
			else {
				if (n != 1 || s == "0") {
					out << -1 << endl;
				}
				else {
					out << s << endl;
				}
			}
			continue;
		}
		--n;
		int max_pow = 0;
		while ((1 << max_pow) < s.length()) {
			++max_pow;
		}
		bool ok = true;
		std::vector<std::set<int>> available(max_pow);
		for (int i = 0; i < max_pow && ok; ++i) {
			const int start_pos = (1 << i) - 1;
			const int delta = (1 << (i + 1));
			int used = 10;
			for (auto& it : vals) {
				it = false;
			}
			for (int pos = start_pos; pos < s.length(); pos += delta) {
				if (pos > 0) {
					vals[get_value(s[pos - 1])] = true;
				}
				if (pos < s.length() - 1) {
					vals[get_value(s[pos + 1])] = true;
				}
				if (s[pos] == '?') {
					continue;
				}
				const int cur = get_value(s[pos]);
				if (used != 10 && used != cur) {
					ok = false;
					break;
				}
				used = cur;
			}
			if (used != 10) {
				if (!vals[used]) {
					available[i].insert(used);
				}
				continue;
			}
			for (int d : range(10)) {
				if (!vals[d]) {
					available[i].insert(d);
				}
			}
		}
		auto& first_vec = available.front();
		first_vec.erase(0);
		for (const auto& it : available) {
			ok &= !it.empty();
		}
		if (!ok) {
			out << -1 << endl;
			continue;
		}
		int fixed_first = -1;
		for (const auto& digit : first_vec) {
			ll total = 1;
			for (int i : range(1, max_pow)) {
				const ll cur = available[i].size() - available[i].count(digit);
				total *= cur;
			}
			if (n < total) {
				fixed_first = digit;
				break;
			}
			n -= total;
		}
		if (fixed_first == -1) {
			out << -1 << endl;
			continue;
		}
		for (int i : range(1, max_pow)) {
			available[i].erase(fixed_first);
		}
		vector<ll> suf(max_pow + 1);
		suf.back() = 1;
		for (int i : downrange(max_pow, 1)) {
			suf[i] = suf[i + 1] * available[i].size();
		}
		std::vector<int> digits{ fixed_first };
		for (int i : range(1, max_pow)) {
			int fixed_digit = -1;
			for (const auto& it : available[i]) {
				if (n < suf[i + 1]) {
					fixed_digit = it;
					break;
				}
				n -= suf[i + 1];
			}
			if (fixed_digit == -1) {
				ok = false;
				break;
			}
			digits.emplace_back(fixed_digit);
		}
		if (!ok) {
			out << -1 << endl;
			continue;
		}
		std::string ans(s.length(), '0');
		for (int i : range(max_pow)) {
			const int delta = (1 << (i + 1));
			for (int pos = (1 << i) - 1; pos < ans.length(); pos += delta) {
				ans[pos] = digits[i] + '0';
			}
		}
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

