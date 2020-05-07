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

template<typename T>
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
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

#include <iterator>

constexpr const int BASE_MOD = 1000000007;  /// caide keep

template<typename T>
inline T& add_mod(T& a, const T b, const T mod = BASE_MOD) {
	if ((a += b) >= mod) {
		a -= mod;
	}
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

	ModInt& operator +=(const ModInt rhs) {
		add_mod(value_, rhs.value_, MOD);
		return *this;
	}

	friend std::ostream& operator <<(std::ostream& out, const ModInt& rhs) {
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

const int MAXN = 20000010;

using Num = ModInt<int, 104857601>;

int r[MAXN];
Num c[MAXN];
char s[MAXN];

double start;

void solve(std::istream& in, std::ostream& out) {
	in >> s;
	start = clock();

	const int n = strlen(s);
	for (int i = 0; i <= n; ++i) {
		r[i] = -n;
	}
	for (int i = 0; i <= n; ++i) {
		c[i] = 0;
	}
	r[0] = 0;
	c[0] = 1;
	for (int i = 0; i < n; ++i) {
		if (i % 10000 == 0) {
			std::cerr << i << " / " << n << " " << (clock() - start) / CLOCKS_PER_SEC << std::endl;
		}
		if (s[i] == '(') {
			for (int i = n; i >= 1; --i) {
				const int x = r[i - 1] + 1;
				if (umax(r[i], x)) {
					c[i] = c[i - 1];
				}
				else if (x == r[i]) {
					c[i] += c[i - 1];
				}
			}
		}
		else {
			for (int i = 0; i < n; ++i) {
				const int x = r[i + 1] + 1;
				if (umax(r[i], x)) {
					c[i] = c[i + 1];
				}
				else if (x == r[i]) {
					c[i] += c[i + 1];
				}
			}
		}
	}
	std::cerr << n << " / " << n << std::endl;
	// return c[0];

	out << c[0] << endl;
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

