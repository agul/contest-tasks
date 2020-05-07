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

using namespace std;

const int points[] = { 100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

inline int get_points(const int place) {
	if (place > 30) {
		return 0;
	}
	return points[place - 1];
}

bool check(std::vector<int>& a) {
	std::sort(all(a), greater<int>());
	return a[9] < 0;
}

void solve(istream& in, ostream& out) {
	vector<int> a(10);
	in >> a;
	for (int i = 0; i < 990; ++i) {
		a.emplace_back(a.back());
	}
	int ans = 0;
	for (int place = 1; place <= 1000; ++place) {
		std::vector<int> b = a;
		const int our = get_points(place);
		int cur = 1;
		for (int j = 9; j >= 0; --j) {
			if (cur == place) {
				++cur;
			}
			b[j] += get_points(cur++) - our;
		}
		for (int j = 10; j < 1000; ++j) {
			/* if (cur == place) {
				++cur;
			} */
			b[j] += get_points(cur++) - our;
		}
		if (check(b)) {
			ans = place;
		}
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

