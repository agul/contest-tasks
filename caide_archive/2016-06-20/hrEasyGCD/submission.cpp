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

template<typename T>
inline T gcd(T a, T b) {
	while (b != 0) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

inline void eratosthenes_sieve(std::vector<bool>& prime) {
	if (prime.size() < 2) {
		prime.assign(prime.size(), false);
		return;
	}
	prime.assign(prime.size(), true);
	prime[0] = prime[1] = false;
	for (size_t i = 4; i < prime.size(); i += 2) {
		prime[i] = false;
	}
	for (size_t i = 3; i * i < prime.size(); i += 2) {
		if (prime[i]) {
			const size_t delta = i << 1;
			for (size_t j = i * i; j < prime.size(); j += delta) {
				prime[j] = false;
			}
		}
	}
}

template<typename T>
inline void primes_vector(const size_t n, std::vector<T>* primes) {
	std::vector<T> result;
	if (n < 2) {
		primes->swap(result);
		return;
	}
	std::vector<bool> prime(n);
	eratosthenes_sieve(prime);
	result.emplace_back(2);
	for (size_t i = 3; i < n; i += 2) {
		if (prime[i]) {
			result.emplace_back(i);
		}
	}
	primes->swap(result);
}

using namespace std;

const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<int> a(n);
	in >> a;
	int g = a.front();
	for (const auto& it : a) {
		g = gcd(g, it);
	}
	std::vector<int> primes;
	primes_vector(MAXN, &primes);
	std::vector<int> divs;
	int min_div = -1;
	for (const auto& it : primes) {
		if (g % it == 0) {
			min_div = it;
			break;
		}
	}
	if (min_div == -1) {
		min_div = g;
	}
	const int ans = k / min_div * min_div;
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

