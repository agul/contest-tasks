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

constexpr const long long LINF = 0x3f3f3f3f3f3f3f3fLL;

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

#include <iterator>

using namespace std;

const int MAXN = 222222;

inline ll calc(const std::vector<ll>& cubes, const ll max_val) {
	ll cnt = 0;
	for (int i = 2; i < MAXN; ++i) {
		cnt += max_val / cubes[i];
	}
	return cnt;
}

void solve(std::istream& in, std::ostream& out) {
	std::vector<ll> cubes(MAXN);
	for (ll i = 0; i < MAXN; ++i) {
		cubes[i] = i * i * i;
	}
	ll L = 1, R = LINF;
	ll n;
	in >> n;
	while (R - L > 1) {
		const ll md = (L + R) >> 1;
		const ll cnt = calc(cubes, md);
		if (cnt < n) {
			L = md;
		}
		else {
			R = md;
		}
	}
	cerr << R << " " << calc(cubes, R) << endl;
	if (calc(cubes, R) != n) {
		out << -1 << endl;
		return;
	}
	out << R << endl;
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

