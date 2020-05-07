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

template<class T> 
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

#ifdef _MSC_VER

#endif

using namespace std;

unordered_map<int, ll> memo;

ll calc(const ll n, const ll r, const ll p) {
	if (n <= 1) {
		return 0;
	}
	const auto it = memo.find(n);
	if (it != memo.end()) {
		return it->second;
	}
	ll x = (n - 1) * p + r;
	for (int i = 2; i <= n; ++i) {
		umin(x, calc((n - 1) / i + 1, r, p) + p * (i - 1) + r);
	}
	return memo[n] = x;
}

void solve(istream& in, ostream& out) {
	ll n, p, r;
	in >> n >> r >> p;
	memo.clear();
	const ll ans = calc(n, r, p);
	out << ans << endl;
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

