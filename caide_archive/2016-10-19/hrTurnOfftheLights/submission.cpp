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

static constexpr long long LINF = 0x3f3f3f3f3f3f3f3fLL;

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

}  // namespace std

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
constexpr IntegerRange<T> inclusiveRange(const T to) {
	return IntegerRange<T>(0, to + 1);
}

using namespace std;

/*
void log_input(std::ostream& out, const int n, const int k, const std::vector<ll>& a) {
	out << n << " " << k << endl;
	for (const auto& it : a) {
		out << it << " ";
	}
	out << endl;
}

void log_output(std::ostream& out, const int n, const ll ans, const int best_mask) {
	out << ans << endl;
	for (int i : range(n)) {
		if (best_mask & (1 << i)) {
			out << i + 1 << " ";
		}
	}
	out << endl;
}

void gen(int& n, int& k, std::vector<ll>& a) {
	n = Random::get(3, MAXN);
	k = Random::get(1, n / 2);
	a.resize(n);
	for (auto& it : a) {
		it = Random::get(1, MAXM);
	}
}

void read(std::istream& in, int& n, int& k, std::vector<ll>& a) {
	in >> n >> k;
	a.resize(n);
	in >> a;
}

std::pair<ll, int> process(const int n, const int k, const std::vector<ll>& a) {
	ll ans = LINF;
	int best_mask = -1;
	for (int mask : range(1 << n)) {
		ll cur = 0;
		vector<bool> lamps(n, true);
		for (int i : range(n)) {
			if ((mask & (1 << i)) == 0) {
				continue;
			}
			for (int j : inclusiveRange(std::max(0, i - k), std::min(n - 1, i + k))) {
				lamps[j] = !lamps[j];
			}
			cur += a[i];
		}
		if (std::count(all(lamps), true) != 0) {
			continue;
		}
		if (umin(ans, cur)) {
			best_mask = mask;
		}
	}
	return{ ans, best_mask };
}

void solve(std::istream& in, std::ostream& out) {
	for (int iteration : range(ITER)) {
		int n, k;
		vector<ll> a;

		gen(n, k, a);
		// read(in, n, k, a);
		log_input(out, n, k, a);

		auto result = process(n, k, a);

		const ll ans = result.first;
		const int best_mask = result.second;

		log_output(out, n, ans, best_mask);

		out << endl;
	}
}

*/

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<ll> a(n);
	in >> a;
	const int delta = k * 2 + 1;
	ll ans = LINF;
	for (int start : inclusiveRange(std::min(n - 1, k))) {
		ll cur = 0;
		int mx = 0;
		for (int pos = start; pos < n; pos += delta) {
			cur += a[pos];
			mx = pos + k;
		}
		if (mx >= n - 1) {
			umin(ans, cur);
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

