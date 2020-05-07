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

#define pii std::pair<int, int>

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

using namespace std;

int __;

inline ll get_c(const ll len) {
	return len * (len + 1) / 2;
}

void add_segment(std::set<pii>& segs, ll& ans, const int x, const int y) {
	if (y < x) {
		return;
	}
	segs.emplace(x, y);
	const ll len = y - x + 1;
	ans += get_c(len);
}

void remove_element(std::set<pii>& segs, ll& ans, const int x) {
	auto it = segs.lower_bound({ x, x });
	if (it == segs.cend() || it->first != x) {
		--it;
	}
	const int fs = it->first;
	const int sc = it->second;
	segs.erase(it);
	const int len = sc - fs + 1;
	ans -= get_c(len);
	add_segment(segs, ans, fs, x - 1);
	add_segment(segs, ans, x + 1, sc);
}

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n;
		in >> n;
		std::unordered_map<int, int> comp;
		std::vector<std::vector<int>> pos(n);
		std::vector<int> a;
		for (int i : range(n)) {
			int x;
			in >> x;
			auto it = comp.find(x);
			int val = 0;
			if (it == comp.cend()) {
				val = comp.size();
				comp[x] = val;
			}
			else {
				val = it->second;
			}
			a.emplace_back(val);
			pos[val].emplace_back(i);
		}
		std::unordered_set<int> used;
		std::set<pii> segs;
		ll ans = 0;
		for (int i : range(n)) {
			used.clear();
			segs.clear();
			ll cur_cnt = 0;
			add_segment(segs, cur_cnt, i, n - 1);
			for (int j : range(i, n)) {
				const int val = a[j];
				if (used.count(val)) {
					ans += cur_cnt;
					continue;
				}
				used.emplace(val);
				for (int k : pos[val]) {
					if (k >= j) {
						remove_element(segs, cur_cnt, k);
					}
				}
				ans += cur_cnt;
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

