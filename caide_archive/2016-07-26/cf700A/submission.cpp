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

constexpr const long double EPS = 1e-9;

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

#include <iterator>

using namespace std;

void solve(std::istream& in, std::ostream& out) {
	out << fixed << setprecision(16);
	double l, pupil_velocity, bus_velocity;
	int n, k;
	in >> n >> l >> pupil_velocity >> bus_velocity >> k;
	if (bus_velocity <= pupil_velocity + EPS) {
		out << l / pupil_velocity << endl;
		return;
	}
	const int runs = (n - 1) / k + 1;
	double L = 0, R = l;
	for (int iter = 0; iter < 100; ++iter) {
		double dist = (L + R) / 2;
		const double forward_time = dist / bus_velocity;
		const double pupil_walk = forward_time * pupil_velocity;
		const double remaining_dist = dist - pupil_walk;
		const double common_velocity = bus_velocity + pupil_velocity;
		const double time_to_meet = remaining_dist / common_velocity;
		const double dist_to_meet = time_to_meet * bus_velocity;
		if (dist + (runs - 1) * (dist - dist_to_meet) > l) {
			R = dist;
		}
		else {
			L = dist;
		}
	}
	double ans = L / bus_velocity + (l - L) / pupil_velocity;
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

