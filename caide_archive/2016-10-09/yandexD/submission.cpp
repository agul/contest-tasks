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

#define ll long long

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

template<typename R, typename Comp>
void sort(R& range, Comp comp) {
	std::sort(range.begin(), range.end(), comp);
}

template<typename T>
inline T gcd(T a, T b) {
	while (b != 0) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

template<typename T>
class Rational {
public:
	static_assert(std::is_integral<T>::value, "Base type of Rational must be an integral.");

	Rational(const T a, const T b) : a_(a), b_(b) {
		normalize();
	}

	constexpr Rational divide(const Rational& rhs) const {
		return{ a_ * rhs.b_, b_ * rhs.a_ };
	}

	constexpr Rational operator /(const Rational& rhs) const {
		return divide(rhs);
	}

	constexpr friend bool operator <(const Rational& lhs, const Rational& rhs) {
		return lhs.a_ * rhs.b_ < rhs.a_ * lhs.b_;
	}

	void normalize() {
		const T g = gcd(a_, b_);
		a_ /= g;
		b_ /= g;
		if (b_ < 0) {
			a_ = -a_;
			b_ = -b_;
		}
	}

private:
	T a_;
	T b_;

};

using namespace std;

using R = Rational<ll>;

bool cmp(const pii& lhs, const pii& rhs) {
	return lhs.first * rhs.second < rhs.first * lhs.second;
}

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<int> a(n);
	in >> a;
	
	vector<pii> items;
	auto parts = make_vector<pii>(n, k, pii(1, 1));
	for (int i : range(n)) {
		for (int j : range(k)) {
			auto cur_part = pii(a[i], j + 1);
			parts[i][j] = cur_part;
			items.emplace_back(cur_part);
		}
	}
	vector<int> ptr(n, k - 1);
	sort(items, cmp);

	R best = R(items.back().first, items.back().second) / R(items.front().first, items.front().second);
	vector<int> ans(n, 0);
	for (const auto& it : items) {
		bool ok = true;
		pii mx(0, 1);
		for (int i : range(n)) {
			int& x = ptr[i];
			while (x > 0 && cmp(parts[i][x], it)) {
				--x;
			}
			if (x == 0 && cmp(parts[i][0], it)) {
				ok = false;
				break;
			}
			if (cmp(mx, parts[i][x])) {
				mx = parts[i][x];
			}
		}
		if (!ok) {
			break;
		}
		R cur_ratio = R(mx.first, mx.second) / R(it.first, it.second);
		if (umin(best, cur_ratio)) {
			ans = ptr;
		}
	}

	for (const auto& it : ans) {
		out << it + 1 << " ";
	}
	out << endl;
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

