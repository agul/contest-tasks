#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <type_traits>

template<typename T>
inline bool is_leap_year(const T year) {
	return year % 400 == 0 || (year % 100 != 0 && (year & 3) == 0);
}

#pragma comment(linker, "/STACK:66777216")
#pragma warning(disable : 4996)

#include <array>
#include <bitset>
#include <cassert>

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

#include <set>
#include <sstream>

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

using namespace std;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	bool leap = is_leap_year(n);
	int cnt = 0;
	while (cnt == 0 || cnt % 7 != 0 || leap != is_leap_year(n)) {
		cnt += 365 + (is_leap_year(n) ? 1 : 0);
		++n;
	}
	out << n << endl;
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

