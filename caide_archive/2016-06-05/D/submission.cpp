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

#define ll int64_t

#ifdef _MSC_VER

#endif

template<typename T, typename U, typename Q>
inline T ppow(T a, U b, Q md) {
	ll ret = 1;
	a %= md;
	while (b) {
		if (b & 1) {
			ret = ret * a % md;
		}
		a = a * a % md;
		b >>= 1;
	}
	return ret % md;
}

template<typename T, typename U>
T inverseElement(const T n, const U mod)
// inverse element for prime mod
{
	return ppow(static_cast<ll>(n), mod - 2, mod);
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

	constexpr ModInt() : ModInt(0) {}

	template<typename U>
	constexpr ModInt(const U value) : value_(normalize(value)) {
		static_assert(MOD > 0, "Modulo must be strictly positive.");
		// static_assert((std::equal<T, int32_t> && mod <= 0x3f3f3f3f) || (std::equal<T, int64_t> && mod <= 0x3f3f3f3f3f3f3f3fLL), "Modulo must be less than half of the max value for typename.");
	}

	constexpr T value() const {
		return value_;
	}

	ModInt operator *(const ModInt rhs) const {
		T x = value_;
		return{ mul_mod(x, rhs.value_, MOD) };
	}

	ModInt& operator +=(const ModInt rhs) {
		add_mod(value_, rhs.value_, MOD);
		return *this;
	}

	ModInt& operator *=(const ModInt rhs) {
		mul_mod(value_, rhs.value_, MOD);
		return *this;
	}

	constexpr ModInt inverse() const {
		return{ inverseElement(static_cast<ll>(value_), MOD) };
	}

private:
	T value_;

	template<typename U>
	T normalize(const U value) const {
		T ret = value % MOD;
		if (ret < 0) {
			return ret + MOD;
		}
		return ret;
	}

};

using namespace std;

const int MAXN = 111111;

inline ModInt<int> C(const std::vector<ModInt<int>>& fact, const std::vector<ModInt<int>>& inv, const int n, const int k) {
	return fact[n] * inv[k] * inv[n - k];
}

inline bool check(int x, int y, int p) {
	if ((x & 1) == (y & 1)) {
		return true;
	}
	x /= 2;
	y /= 2;
	if (x >= p || y >= p) {
		return false;
	}
	return x == y;
}

int brute(const int m, const int w, const int p) {
	std::vector<int> perm;
	for (int i = 0; i < m; ++i) {
		perm.emplace_back(i * 2);
	}
	for (int i = 0; i < w; ++i) {
		perm.emplace_back(i * 2 + 1);
	}
	int ans = 0;
	std::sort(perm.begin(), perm.end());
	do {
		bool ok = true;
		for (int i = 1; i < perm.size(); ++i) {
			ok &= check(perm[i - 1], perm[i], p);
		}
		ans += (ok ? 1 : 0);
	} while (next_permutation(perm.begin(), perm.end()));
	return ans;
}

int solve(const std::vector<ModInt<int>>& fact, const std::vector<ModInt<int>>& inv, const int m, const int w, const int p) {
	if (m == 0 || w == 0) {
		return fact[m + w].value();
	}
	ModInt<int> ans = 0;
	for (int pairs = 0; pairs <= p; ++pairs) {
		const int alone_w = w - pairs;
		const int alone_m = m - pairs;
		{
			ModInt<int> cur = 1;
			cur *= fact[pairs];
			cur *= C(fact, inv, p, pairs);

			const int places_w = (pairs >> 1) + (pairs & 1);
			cur *= (places_w == 0 ? 0 : fact[alone_w + places_w - 1] * inv[places_w - 1]);

			const int places_m = (pairs >> 1) + 1;
			cur *= (places_m == 0 ? 0 : fact[alone_m + places_m - 1] * inv[places_m - 1]);

			ans += cur;

		}
		{
			ModInt<int> cur = 1;
			cur *= fact[pairs];
			cur *= C(fact, inv, p, pairs);

			const int places_m = (pairs >> 1) + (pairs & 1);
			cur *= (places_m == 0 ? 0 : fact[alone_m + places_m - 1] * inv[places_m - 1]);

			const int places_w = (pairs >> 1) + 1;
			cur *= (places_w == 0 ? 0 : fact[alone_w + places_w - 1] * inv[places_w - 1]);

			ans += cur;

		}

	}
	return ans.value();
}

void solve(istream& in, ostream& out) {
	std::vector<ModInt<int>> fact(MAXN * 2);
	std::vector<ModInt<int>> inv(MAXN * 2);

	fact[0] = inv[0] = 1;
	for (size_t i = 1; i < fact.size(); ++i) {
		fact[i] = fact[i - 1] * i;
		inv[i] = fact[i].inverse();
	}
	int m, w, p;
	in >> m >> w >> p;
	int ans = solve(fact, inv, m, w, p); out << ans << endl; return;
	for (m = 0; m <= 10; ++m) {
		for (w = 0; w <= 10; ++w) {
			for (p = 0; p <= min(m, w); ++p) {
				if (m + w == 0 || m + w > 10) {
					continue;
				}
				int pans = solve(fact, inv, m, w, p);
				int jans = brute(m, w, p);
				if (pans != jans) {
					std::cerr << "WTF!!! " << m << " " << w << " " << p << " " << jans << " " << pans << std::endl;
				}
			}
		}
	}
	std::cerr << "OK" << std::endl;
	// out << pans << endl;
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

