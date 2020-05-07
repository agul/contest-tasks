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

template<typename R>
void sort(R& range) {
	std::sort(range.begin(), range.end());
}

namespace Random {

	static std::chrono::system_clock::rep GetRandSeed() {
		return std::chrono::system_clock::now().time_since_epoch().count();
	}

}

class DSU {
public:
	
	DSU(const size_t vertices_count) : parent_(vertices_count), sets_count_(vertices_count) {
		srand(static_cast<uint32_t>(Random::GetRandSeed()));
		std::iota(parent_.begin(), parent_.end(), 0);
	}

	size_t find_set(const size_t vertex) {
		if (vertex != parent_[vertex]) {
			parent_[vertex] = find_set(parent_[vertex]);
		}
		return parent_[vertex];
	}

	bool unite(const size_t a, const size_t b) {
		size_t x = find_set(a);
		size_t y = find_set(b);
		if (x == y) {
			return false;
		}
		if ((rand() & 1) != 0) {
			std::swap(x, y);
		}
		parent_[x] = y;
		--sets_count_;
		return true;
	}

private:
	std::vector<size_t> parent_;
	size_t sets_count_;

};

using namespace std;

int __;

struct Edge {
	int from, to, weight;

	Edge(const int from, const int to, const int weight) : from(from), to(to), weight(weight) {}

	bool operator < (const Edge& rhs) const {
		return weight < rhs.weight;
	}
};

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n;
		string s;
		in >> n >> s;
		vector<int> a(n);
		in >> a;
		DSU dsu(n + 1);
		std::vector<Edge> edges;
		for (int i : range(n)) {
			if (s[i] == '1') {
				dsu.unite(0, i + 1);
			}
			if (i > 0) {
				edges.emplace_back(i, i + 1, a[i] - a[i - 1]);
			}
		}
		sort(edges);
		ll ans = 0;
		for (const auto& it : edges) {
			if (dsu.unite(it.from, it.to)) {
				ans += it.weight;
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

