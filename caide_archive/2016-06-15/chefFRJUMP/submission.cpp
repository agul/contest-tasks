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

template<typename T, typename U, typename Q>
inline T binpow(T a, U b, Q mod) {
	static_assert(std::is_integral<U>::value, "Degree must be integral. For real degree use pow.");
	long long ret = 1;
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
	return binpow(static_cast<long long>(n), mod - 2, mod);
}

constexpr const int BASE_MOD = 1000000007;  /// caide keep

template<typename T>
inline T& add_mod(T& a, const T b, const T mod = BASE_MOD) {
	if ((a += b) >= mod) {
		a -= mod;
	}
	return a;
}

template<typename T>
inline T& mul_mod(T& a, const T b, const T mod = BASE_MOD) {
	a = static_cast<long long>(a) * b % mod;
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

	ModInt& operator *=(const ModInt rhs) {
		mul_mod(value_, rhs.value_, MOD);
		return *this;
	}

	constexpr ModInt inverse() const {
		return{ inverseElement(static_cast<long long>(value_), MOD) };
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

struct Result {
	long double exact, value;
	ModInt<int> rem;
	bool exact_fail;

	Result() : Result(1) {}
	Result(const int v) : exact(v), value(v), rem(v), exact_fail(false) {}

	void operator *= (const int rhs) {
		exact *= rhs;
		value *= rhs;
		rem *= rhs;
		normalize();
	}

	void operator /= (const int rhs) {
		rem *= ModInt<int>(rhs).inverse();
		while (exact < rhs) {
			exact *= 10;
		}
		exact /= rhs;
		while (value < rhs) {
			value *= 10;
		}
		value /= rhs;
	}

	void normalize() {
		while (exact >= 10000000000LL) {
			exact /= 10;
			exact_fail = true;
		}
		while (value >= 10) {
			value /= 10;
		}
	}

	int get_first_digit() const {
		ll tmp = static_cast<ll>(exact_fail ? value : exact);
		while (tmp >= 10) {
			tmp /= 10;
		}
		return tmp;
	}

};

const size_t MAXK = 0;

void solve(std::istream& in, std::ostream& out) {
	size_t n;
	in >> n;
	vector<ll> a(n);
	in >> a >> __;
	vector<Result> res(n + 1);
	vector<vector<int>> divs(n + 1);
	for (int i = 1; i <= std::min(MAXK, n); ++i) {
		for (int j = i; j <= n; j += i) {
			divs[j].emplace_back(i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j < n; j += i) {
			res[i] *= a[j];
		}
	}
	for (int _ = 0; _ < __; ++_) { 
		int type;
		in >> type;
		if (type == 1) {
			int index, value;
			in >> index >> value;
			--index;
			if (index != 0) {
				for (const auto& div : divs[index]) {
					res[div] /= a[index];
					res[div] *= value;
				}
			}
			a[index] = value;
			continue;
		}
		int value;
		in >> value;
		Result tmp = res[value];
		if (value >= MAXK) {
			tmp = Result(1);
			for (int i = value; i < n; i += value) {
				tmp *= a[i];
			}
		}
		tmp *= a.front();
		out << tmp.get_first_digit() << " " << tmp.rem << endl;
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

