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
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

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

constexpr const int32_t BASE_MOD = 1000000007;  /// caide keep

template<typename T>
inline T& add_mod(T& a, const T b, const T mod = BASE_MOD) {
	if ((a += b) >= mod) {
		a -= mod;
	}
	return a;
}

template<typename T, T MOD = BASE_MOD>
class ModInt {
public:

	/// caide keep
	constexpr ModInt() : ModInt(0) {}

private:
	T value_;

};

using namespace std;

const int MAXN = 1111111;

class Warrior {
public:
	ll a, b, c;

	Warrior() = default;

	friend istream& operator >>(istream& in, Warrior& rhs) {
		in >> rhs.a >> rhs.b >> rhs.c;
		return in;
	}

};

void solve(istream& in, ostream& out) {
	int n;
	ll m;
	in >> n >> m;
	vector<Warrior> a(n);
	in >> a;
	vector<int> lose(MAXN);
	vector<ll> sum(n + 1);
	for (int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1] + a[i - 1].b;
	}
	int battle = 0;
	for (int i = 0; i < MAXN; ++i) {
		while (battle < n && sum[battle] + i < MAXN && a[battle].a < sum[battle] + i) {
			++battle;
		}
		if (battle == n || sum[battle] + i >= MAXN) {
			for (int j = i; j < MAXN; ++j) {
				lose[j] = n;
			}
			break;
		}
		lose[i] = battle;
	}
	ll ans = 0;
	std::vector<bool> used(MAXN);
	int pos = 0;
	ll strength = m;
	while (true) {
		if (strength >= MAXN) {
			ans += n;
			break;
		}
		if (used[strength]) {
			out << -1 << endl;
			return;
		}
		used[strength] = true;
		const int pos = lose[strength];
		if (pos == n) {
			ans += n;
			break;
		}
		ans += pos + 1;
		strength += sum[pos] - a[pos].c;
		umax(strength, 0LL);
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

