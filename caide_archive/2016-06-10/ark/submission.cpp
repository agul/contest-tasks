#pragma comment(linker, "/STACK:66777216")

#include <cstdio>
#pragma warning(disable : 4996)
#include <algorithm>
#include <array>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <utility>
#include <functional>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <queue>
#include <cmath>
#include <random>
#include <sstream>
#include <numeric>
#include <limits>
#include <chrono>
#include <type_traits>
#pragma hdrstop

#ifdef _MSC_VER
#include <intrin.h>

#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#define all(a) a.begin(), a.end()

#define ll int64_t

#ifdef _MSC_VER

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

template<typename T, typename U, typename Q>
inline T binpow(T a, U b, Q mod) {
	static_assert(std::is_integral<U>::value, "Degree must be integral. For real degree use pow.");
	ll ret = 1;
	a %= mod;
	while (b != 0) {
		if ((b & 1) != 0) {
			ret = ret * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return ret % mod;
}

template<typename T, typename U>
T inverseElement(const T n, const U mod)
// inverse element for prime mod
{
	return binpow(static_cast<ll>(n), mod - 2, mod);
}

constexpr const int32_t BASE_MOD = 1000000007;

template<typename T>
inline T& add_mod(T& a, const T b, const T mod = BASE_MOD) {
	if ((a += b) >= mod) {
		a -= mod;
	}
	return a;
}

template<typename T>
inline T& mul_mod(T& a, const T b, const T mod = BASE_MOD) {
	a = static_cast<ll>(a) * b % mod;
	return a;
}

template<typename T, T MOD = BASE_MOD>
class ModInt {
public:

	/// caide keep
	constexpr ModInt() : ModInt(0) {}

	template<typename U>
	constexpr ModInt(const U value) : value_(normalize(value)) {
		static_assert(MOD > 0, "Modulo must be strictly positive.");
		// static_assert((std::equal<T, int32_t> && mod <= 0x3f3f3f3f) || (std::equal<T, int64_t> && mod <= 0x3f3f3f3f3f3f3f3fLL), "Modulo must be less than half of the max value for typename.");
	}

	ModInt operator *(const ModInt rhs) const {
		T x = value_;
		return{ mul_mod(x, rhs.value_, MOD) };
	}

	ModInt& operator +=(const ModInt rhs) {
		add_mod(value_, rhs.value_, MOD);
		return *this;
	}

	constexpr ModInt inverse() const {
		return{ inverseElement(static_cast<ll>(value_), MOD) };
	}

	friend std::ostream& operator <<(std::ostream& out, ModInt& rhs) {
		out << rhs.value_;
		return out;
	}

private:
	T value_;

	template<typename U>
	T normalize(const U value) const {
		if (value >= 0 && value < MOD) {
			return value;
		}
		const T ret = value % MOD;
		if (ret < 0) {
			return ret + MOD;
		}
		return ret;
	}

};

using namespace std;

int __;

const int MAXN = 1111111;

ModInt<int> c(const std::vector<ModInt<int>>& fact, const std::vector<ModInt<int>>& inv, int n, int k) {
	if (n < k) {
		return 0;
	}
	return fact[n] * inv[k] * inv[n - k];
}

void solve(istream& in, ostream& out) {
	in >> __;
	vector<ModInt<int>> fact(MAXN);
	vector<ModInt<int>> inv(MAXN);
	fact.front() = inv.front() = 1;
	for (int i = 1; i < MAXN; ++i) {
		fact[i] = fact[i - 1] * i;
		inv[i] = fact[i].inverse();
	}
	for (int _ = 0; _ < __; ++_) {
		int n, k;
		in >> n >> k;
		vector<int> a(n);
		in >> a;
		const size_t zeroes = count(all(a), 0);
		const size_t non_zeroes = n - zeroes;
		ModInt<int> ans = 0;
		const size_t start = (zeroes == 0 ? k & 1 : 0);
		const size_t delta = (zeroes == 0 ? 2 : 1);
		for (size_t i = start; i <= k; i += delta) {
			ans += c(fact, inv, non_zeroes, i);
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

