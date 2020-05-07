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

#define ll int64_t

#ifdef _MSC_VER

#endif

using namespace std;

const int MAXN = 111111;

struct Generator {
public:

	Generator() : value_(0) {}

	ll operator()() {
		ll x = value_++;
		return x * x * x;
	}

private:
	ll value_;
};

struct Result {
	ll num;
	int cnt;

	Result() : num(0), cnt(0) {}
	Result(const ll num, const int cnt) : num(num), cnt(cnt) {}

	bool operator < (const Result& rhs) const {
		return cnt < rhs.cnt || (cnt == rhs.cnt && num < rhs.num);
	}

	Result operator + (const Result& rhs) const {
		return{ num + rhs.num, cnt + rhs.cnt };
	}

	friend ostream& operator <<(ostream& out, const Result& rhs) {
		out << rhs.cnt << " " << rhs.num;
		return out;
	}

};

ll get_closest_cube(const std::vector<ll>& cubes, const ll value) {
	auto it = std::upper_bound(all(cubes), value);
	return *--it;
}

int process(const std::vector<ll>& cubes, const ll value) {
	ll tmp = value;
	int cnt = 0;
	while (tmp > 0) {
		ll v = get_closest_cube(cubes, tmp);
		tmp -= v;
		++cnt;
	}
	return cnt;
}

Result go(const std::vector<ll>& cubes, const std::vector<Result>& mx, const ll value) {
	if (value < mx.size()) {
		return mx[value];
	}
	const ll a = get_closest_cube(cubes, value);
	const ll b = get_closest_cube(cubes, a - 1);

	const Result x = go(cubes, mx, value - a) + Result(a, 1);
	const Result y = go(cubes, mx, a - b) + Result(b, 1);
	return std::max(x, y);
}

void solve(istream& in, ostream& out) {
	Generator generator;
	vector<ll> cubes(MAXN);
	std::generate(cubes.begin(), cubes.end(), generator);
	vector<Result> mx(MAXN);
	for (int i = 1; i < MAXN; ++i) {
		mx[i] = max(mx[i - 1], { i, process(cubes, i) });
	}
	ll n;
	in >> n;
	const Result best_value = go(cubes, mx, n);
	out << best_value << endl;
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

