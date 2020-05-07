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

#define fill(a, x) memset(a, x, sizeof(a))

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
constexpr ReversedIntegerRange<T> inclusiveDownrange(const T from) {
	return ReversedIntegerRange<T>(from + 1, 0);
}

template<typename R>
void reverse(R& range) {
	std::reverse(range.begin(), range.end());
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
inline T lcm(const T& a, const T& b) {
	return a / gcd(a, b) * b;
}

template<typename T>
void binomial_coefficients(const size_t n, std::vector<std::vector<T>>* c) {
	std::vector<std::vector<T>> result(n, std::vector<T>(n));
	for (size_t i = 0; i < n; ++i) {
		result[i][0] = 1;
		result [i][i] = 1;
		for (size_t j = 1; j < i; ++j) {
			result[i][j] = result[i - 1][j - 1] + result[i - 1][j];
		}
	}
	c->swap(result);
}

template<typename T>
class Combination : public std::vector<T> {
public:
	Combination(const size_t n, const size_t k) : std::vector<T>(k), n_(n) {
		init();
	}

	void init() {
		std::iota(this->begin(), this->end(), 0);
	}

	bool next() {
		const size_t k = this->size();
		Combination tmp = *this;
		size_t index = k;
		do {
			--index;
			if (tmp[index] < n_ - k + index) {
				++tmp[index];
				for (size_t j = index + 1; j < k; ++j) {
					tmp[j] = tmp[j - 1] + 1;
				}
				this->swap(tmp);
				return true;
			}
		} while (index > 0);
		init();
		return false;
	}

private:
	size_t n_;

};

using namespace std;

int __;
const int MOD = 2520;

ll dp[20][MOD][512][2];
std::vector<int> sup_masks[512];
std::vector<std::vector<int>> binoms;

std::vector<int> get_digits(const ll n) {
	std::vector<int> res;
	ll tmp = n;
	while (tmp > 0) {
		res.emplace_back(static_cast<int>(tmp % 10));
		tmp /= 10;
	}
	return res;
}

ll get_ans(const ll n, const int k) {
	if (n == 0) {
		return 0;
	}
	if (k == 0) {
		return n;
	}
	auto digits = get_digits(n);
	const int num_len = digits.size();

	reverse(digits);
	fill(dp, 0);
	dp[0][0][0][1] = 1;
	for (int pos : range(num_len)) {
		for (int rem : range(MOD)) {
			for (int mask : range(512)) {
				for (int prefix : range(2)) {
					const ll cur_val = dp[pos][rem][mask][prefix];
					if (cur_val == 0) {
						continue;
					}
					int finish = 10;
					if (prefix == 1) {
						finish = digits[pos] + 1;
					}
					for (int next_digit : range(finish)) {
						int new_rem = (rem * 10 + next_digit) % MOD;
						int new_mask = mask;
						if (next_digit != 0) {
							new_mask |= (1 << (next_digit - 1));
						}
						int new_prefix = 0;
						if (prefix && next_digit == digits[pos]) {
							new_prefix = 1;
						}
						dp[pos + 1][new_rem][new_mask][new_prefix] += cur_val;
					}
				}
			}
		}
	}

	std::vector<ll> total_cnt(11);
	for (int len : range(1, 10)) {
		Combination<int> comb(9, len);
		do {
			int mask = 0;
			int cur_lcm = 1;
			for (const auto& it : comb) {
				mask |= (1 << it);
				cur_lcm = lcm(cur_lcm, it + 1);
			}
			ll cur_val = 0;
			for (const auto& sup_mask : sup_masks[mask]) {
				for (int rem = 0; rem < MOD; rem += cur_lcm) {
					for (int prefix : range(2)) {
						cur_val += dp[num_len][rem][sup_mask][prefix];
					}
				}
			}
			total_cnt[len] += cur_val;
		} while (comb.next());
	}
	std::vector<ll> real_cnt(11);
	std::vector<ll> pref(11, 0);
	for (int i : inclusiveDownrange(9)) {
		real_cnt[i] = total_cnt[i];
		int used = 1;
		for (int j : range(i + 1, 10)) {
			int need = binoms[j][i] - used;
			real_cnt[i] -= real_cnt[j] * need;
			used += need;
		}
	}
	return real_cnt[k];
}

void solve(std::istream& in, std::ostream& out) {
	binomial_coefficients(10, &binoms);
	for (int mask : range(512)) {
		sup_masks[mask].clear();
	}
	for (int mask : range(512)) {
		for (int submask = mask; submask != 0; submask = (submask - 1) & mask) {
			sup_masks[submask].emplace_back(mask);
		}
	}
	in >> __;
	for (int _ : range(__)) {
		ll L, R;
		int k;
		in >> L >> R >> k;
		const ll ans = get_ans(R, k) - get_ans(L - 1, k);
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

