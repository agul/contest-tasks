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


namespace std {


}

#ifdef _MSC_VER

#endif


template<class T> inline T sqr(const T& x) {
	return x * x;
}

template<class T> inline bool isPrime(const T& n)
// Straightforward checking in O(sqrt(N))
{
	if (n < 2) {
		return false;
	}
	T kk = (T)sqrt(n + 0.);
	for (T i = 2; i <= kk; ++i) {
		if (!(n % i)) {
			return false;
		}
	}
	return true;
}


namespace Random {


}


class ExploringNumbers {
public:

	int get_sum(const int n) const {
		int x = n;
		int sum = 0;
		while (x > 0) {
			sum += sqr(x % 10);
			x /= 10;
		}
		return sum;
	}

    /// caide keep
    int numberOfSteps(const int n) {
		int last = n;
		int step;
		std::vector<bool> used(1000, false);
		for (step = 1; step <= n && !isPrime(last); ++step) {
			last = get_sum(last);
			if (used[last]) {
				break;
			}
			used[last] = true;
		}
		if (!isPrime(last)) {
			return -1;
		}
		return step;
    }
};


//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);
