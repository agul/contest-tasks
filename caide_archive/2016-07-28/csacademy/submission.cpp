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

#define all(a) a.begin(), a.end()

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#define ll long long

#define pii std::pair<int, int>

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

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<ll> a(n);
	vector<int> p(n);
	in >> a >> p;
	for (auto& it : p) {
		--it;
	}
	ll sum = std::accumulate(all(a), 0LL);
	vector<ll> pref(n + 1);
	pref[0] = 0;
	partial_sum(all(a), pref.begin() + 1);
	std::multiset<ll, std::greater<ll>> sums;
	sums.emplace(sum);
	std::set<pii> vals;
	vals.emplace(pii( 0, n - 1 ));
	for (const auto& pos : p) {
		const ll ans = *sums.begin();
		out << ans << endl;
		auto it = vals.lower_bound({pos, pos});
		if (it == vals.end() || it->first > pos) {
			--it;
		}
		const int L = it->first;
		const int R = it->second;
		vals.erase(it);
		sums.erase(sums.find(pref[R + 1] - pref[L]));
		if (pos > L) {
			vals.emplace(L, pos - 1);
			sums.emplace(pref[pos] - pref[L]);
		}
		if (pos < R) {
			vals.emplace(pos + 1, R);
			sums.emplace(pref[R + 1] - pref[pos + 1]);
		}
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

