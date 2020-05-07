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

constexpr const int INF = 0x3f3f3f3f;

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

template<typename T>
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
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

#define fill(a, x) memset(a, x, sizeof(a))

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

using namespace std;

const int MAXN = 111;

int dp[MAXN][4];

const int CF = 1;
const int GYM = 2;

inline bool is_cf(const int x) {
	return x == 1 || x == 3;
}

inline bool is_gym(const int y) {
	return y == 2 || y == 3;
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<int> a(n);
	in >> a;
	fill(dp, INF);
	dp[0][0] = 0;
	for (int i = 0; i < n; ++i) {
		const int day = a[i];
		for (int task = 0; task < 3; ++task) {
			if (task != CF && is_cf(day)) {
				umin(dp[i + 1][CF], dp[i][task]);
			}
			if (task != GYM && is_gym(day)) {
				umin(dp[i + 1][GYM], dp[i][task]);
			}
			umin(dp[i + 1][0], dp[i][task] + 1);
		}
	}
	int ans = INF;
	for (int i = 0; i < 3; ++i) {
		umin(ans, dp[n][i]);
	}
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

