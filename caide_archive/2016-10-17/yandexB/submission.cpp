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
constexpr ReversedIntegerRange<T> downrange(const T from) {
	return ReversedIntegerRange<T>(from, 0);
}

using namespace std;

  // namespace brute

using Strategy = std::function<int(const std::vector<int>&, std::istream&, std::ostream&, bool)>;

namespace alex {

	void print(const int sum, const std::vector<int>& ans, const std::vector<int>& a, std::istream& in, std::ostream& out) {
		const int n = a.size();
		out << sum << endl;
		int total_money = 0;
		int total_bonus = 0;
		for (int i : range(n)) {
			const int money = ans[i];
			const int bonus = a[i] - money;
			out << money << " + " << bonus << endl;
			assert(money + bonus == a[i]);
			assert(money >= 0);
			assert(money <= a[i]);
			assert(bonus <= total_bonus);
			if (bonus == 0) {
				total_bonus += money / 100;
			}
			total_money += money;
			total_bonus -= bonus;
		}
		assert(total_money == sum);
	}

}

int stupid_strategy(const std::vector<int>& a, std::istream& in, std::ostream& out, bool dry_run) {
	const int n = a.size();
	vector<int> prefsum(n + 1);
	for (int i : range(n)) {
		prefsum[i + 1] = prefsum[i] + a[i] / 100;
	}
	vector<int> ans = a;
	int bottom = 0;
	for (int i : downrange(n)) {
		if (prefsum[i + 1] == bottom) {
			break;
		}
		if (prefsum[i] < bottom) {
			bottom -= a[i] / 100;
		}
		else {
			const int rest = min(a[i], prefsum[i] - bottom);
			ans[i] = a[i] - rest;
			bottom += rest;
		}
	}

	int sum = 0;
	for (int it : ans) {
		sum += it;
	}
	if (!dry_run) {
		alex::print(sum, ans, a, in, out);
	}
	return sum;
}

namespace nastya {

	bool good(const std::vector<int>& p, std::istream& in, std::ostream& out, int lim, bool dry_run) {
		const int n = p.size();
		ll my = lim, bonus = 0;
		for (int i = 0; i < n; i++) {
			if (p[i] <= my) {
				if (!dry_run) out << p[i] << " + 0" << endl;
				my -= p[i];
				bonus += p[i] / 100;
			}
			else {
				if (my + bonus < p[i]) return 0;
				ll lim = min(bonus, 1ll * p[i]);
				if (!dry_run) out << (p[i] - lim) << " + " << lim << endl;
				my -= p[i] - lim;
				bonus -= lim;
			}
		}
		return 1;
	}

}

int nastya_strategy(const std::vector<int>& p, std::istream& in, std::ostream& out, bool dry_run) {
	int lf = 1, rg = 1e9;
	while (lf + 1 < rg) {
		int md = (lf + rg) >> 1;
		if (nastya::good(p, in, out, md, true)) rg = md;
		else lf = md;
	}
	int ans;
	if (nastya::good(p, in, out, lf, true)) ans = lf;
	else ans = rg;
	if (!dry_run) {
		out << ans << endl;
		nastya::good(p, in, out, ans, dry_run);
	}
	return ans;
}

void solve(std::istream& in, std::ostream& out) {
	// brute::solve(in, out); return;
	int n;
	in >> n;
	vector<int> a(n);
	in >> a;

	vector<Strategy> strategies{
		stupid_strategy,
		// damn_strategy,
		// forward_strategy,
		nastya_strategy
	};

	vector<int> values;
	for (const auto& strategy : strategies) {
		const int answer = strategy(a, in, out, true);
		values.emplace_back(answer);
	}
	
	const auto min_elem_iter = min_element(values.begin(), values.end());
	const auto strategy_iter = strategies.begin() + std::distance(values.begin(), min_elem_iter);
	const Strategy strategy = *strategy_iter;
	strategy(a, in, out, false);
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

