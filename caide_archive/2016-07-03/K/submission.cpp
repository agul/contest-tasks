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

template<typename T>
constexpr IntegerRange<T> range(const T from, const T to) {
	return IntegerRange<T>(from, to);
}

using namespace std;

vector<int> cnt;

struct Cmp {
	bool operator()(const int& lhs, const int& rhs) const {
		return cnt[lhs] < cnt[rhs] || (cnt[lhs] == cnt[rhs] && lhs < rhs);
	}
};

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<int> a(2 * n);
	cnt.assign(2 * n, 0);
	in >> a;
	for (auto& it : a) {
		--it;
		++cnt[it];
	}
	set<int, Cmp> vals;
	for (int i : range(2 * n)) {
		vals.insert(i);
	}
	set<int> p, q;
	for (int i : range(n)) {
		p.insert(i);
	}
	for (int j : range(n, 2 * n)) {
		q.insert(j);
	}
	std::vector<int> ans;
	while (!vals.empty()) {
		auto it = vals.begin();
		int x = *it;
		vals.erase(it);
		(x < n ? p : q).erase(x);
		ans.emplace_back(x);
		if (cnt[x] != 0) {
			for (const auto& it : p) {
				ans.emplace_back(it);
			}
			break;
		}

		{
			int to = a[x];
			auto it = vals.find(to);
			if (it != vals.end()) {
				vals.erase(it);
				(to < n ? p : q).erase(to);
				int tto = a[to];
				auto jt = vals.find(tto);
				if (jt != vals.end()) {
					vals.erase(jt);
					--cnt[tto];
					vals.insert(tto);
				}
			}
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

