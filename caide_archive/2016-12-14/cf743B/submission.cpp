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

  // namespace std

#include <iterator>

using namespace std;

void solve(std::istream& in, std::ostream& out) {
	int n;
	ll k;
	in >> n >> k;
	ll cnt = (1LL << n) - 1;
	int step = n;
	while (k >= 1) {
		ll half_cnt = cnt / 2;
		if (k == half_cnt + 1) {
			out << step << endl;
			return;
		}
		if (k > half_cnt) {
			k -= half_cnt + 1;
		}
		cnt /= 2;
		--step;
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

