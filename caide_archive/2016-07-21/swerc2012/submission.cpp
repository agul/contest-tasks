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

constexpr const long double EPS = 1e-9;

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

template<typename R>
auto max_element(const R& range) -> decltype(range.begin()) {
	return std::max_element(range.begin(), range.end());
}

namespace safe {

template<typename T>
constexpr T abs(const T arg) {
	return arg < 0 ? -arg : arg;
}

template<typename T>
constexpr bool is_zero(const T arg) {
	return abs(arg) < EPS;
}

template<typename T>
constexpr bool equal(const T lhs, const T rhs) {
	return is_zero(lhs - rhs);
}

template<typename T>
constexpr bool not_equal(const T lhs, const T rhs) {
	return !equal(lhs, rhs);
}

template<typename T>
constexpr bool less(const T lhs, const T rhs) {
	return lhs < rhs && !equal(lhs, rhs);
}

template<typename T>
constexpr bool greater(const T lhs, const T rhs) {
	return less(rhs, lhs);
}

}

class Decimal {
public:
	/// caide keep
	using T = long double;

	/// caide keep
	constexpr Decimal() : Decimal(0) {}
	constexpr Decimal(const T value) : value_(value) {}

	Decimal& operator -=(const Decimal& rhs) {
		value_ -= rhs.value_;
		return *this;
	}

	constexpr Decimal operator +(const Decimal& rhs) const {
		return{ value_ + rhs.value_ };
	}

	constexpr Decimal operator -(const Decimal& rhs) const {
		return{ value_ - rhs.value_ };
	}

	constexpr Decimal operator *(const Decimal& rhs) const {
		return{ value_ * rhs.value_ };
	}

	constexpr Decimal operator /(const Decimal& rhs) const {
		return{ value_ / rhs.value_ };
	}

	constexpr bool operator ==(const Decimal& rhs) const {
		return safe::equal(value_, rhs.value_);
	}

	constexpr bool operator !=(const Decimal& rhs) const {
		return safe::not_equal(value_, rhs.value_);
	}

	constexpr bool operator <(const Decimal& rhs) const {
		return safe::less(value_, rhs.value_);
	}

	constexpr bool operator >(const Decimal& rhs) const {
		return safe::greater(value_, rhs.value_);
	}

private:
	T value_;

};

using namespace std;

void solve(std::istream& in, std::ostream& out) {
	string s;
	while (getline(in, s)) {
		stringstream ss;
		ss << s;
		int d, p;
		ss >> d >> p;
		int x;
		vector<Decimal> a;
		while (ss >> x) {
			a.emplace_back(x);
		}
		{
			Decimal x = *max_element(a);
			if (x == 0) {
				out << "The spider may fall!" << endl;
				continue;
			}
		}
		if (a.size() <= d) {
			std::vector<std::vector<Decimal>> matrix(2);
			matrix[0] = { a[0], a[1], a[2] };
			matrix[1] = { a[1], a[2], a[3] };
			int cur = 0;
			for (int col : range(3)) {
				bool found = false;
				for (int row : range(cur, 2)) {
					if (matrix[row][col] != 0) {
						found = true;
						matrix[row].swap(matrix[cur]);
						break;
					}
				}
				if (!found) {
					continue;
				}
				for (int row : range(cur + 1, 2)) {
					const Decimal mul = matrix[row][col] / matrix[cur][col];
					for (int c : range(col, 3)) {
						matrix[row][c] -= mul * matrix[cur][c];
					}
				}

				++cur;
			}
			Decimal x1, x2;
			if (matrix[1][1] == 0) {
				x1 = 0;
				x2 = matrix[0][2] / matrix[0][1];
			}
			else {
				x2 = matrix[1][2] / matrix[1][1];
				x1 = (matrix[0][2] - matrix[0][1] * x2) / matrix[0][0];
			}
			for (int i : range((int)a.size(), d + 1)) {
				a.emplace_back(a[i - 2] * x1 + a[i - 1] * x2);
			}
		}
		int ans = -1;
		for (int i = 0; i < a.size(); ++i) {
			if (a[i] > p) {
				break;
			}
			ans = i;
		}
		if (ans == -1) {
			out << "The spider is going to fall!" << endl;
			continue;
		}
		if (ans == d) {
			out << "The spider may fall!" << endl;
			continue;
		}
		out << d - ans << endl;
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

