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

template<typename R>
void sort(R& range) {
	std::sort(range.begin(), range.end());
}

template<typename R>
bool next_permutation(R& range) {
	return std::next_permutation(range.begin(), range.end());
}

using namespace std;

int __;

bool go(const ll h, const ll w, const std::vector<ll>& vals, const int pos) {
	if (pos == 2) {
		return h * w == vals.back();
	}
	if (h * w < vals[pos]) {
		return false;
	}
	ll L = 1, R = w + 1;
	while (R - L > 1) {
		ll md = (L + R) >> 1;
		if (h * md > vals[pos]) {
			R = md;
		}
		else {
			L = md;
		}
	}
	bool ok = false;
	if (h * L == vals[pos]) {
		ok |= go(h, w - L, vals, pos + 1);
	}
	L = 1, R = h + 1;
	while (R - L > 1) {
		ll md = (L + R) >> 1;
		if (w * md > vals[pos]) {
			R = md;
		}
		else {
			L = md;
		}
	}
	if (w * L == vals[pos]) {
		ok |= go(h - L, w, vals, pos + 1);
	}
	return ok;
}

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		ll h, w;
		vector<ll> vals(3);
		in >> h >> w >> vals;
		bool ok = false;
		sort(vals);
		do {
			ok |= go(h, w, vals, 0);
		} while (next_permutation(vals));
		out << (ok ? "Yes" : "No") << endl;
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

