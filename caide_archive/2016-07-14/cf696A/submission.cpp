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

namespace std {

template<typename T, typename U>
struct hash<std::pair<T, U>> {
	std::size_t operator()(const std::pair<T, U>& lhs) const {
		return lhs.first * 877117 + lhs.second;
	}
};

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

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#define ll long long

#define pll std::pair<ll, ll>

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

struct Query {
	ll a, b;
	ll cost;
	ll lca;
	int type;
	
	Query() : a(0), b(0), cost(0), lca(0), type(0) {}

	friend istream& operator >>(istream& in, Query& rhs) {
		in >> rhs.type >> rhs.a >> rhs.b;
		if (rhs.type == 1) {
			in >> rhs.cost;
		}

		std::unordered_set<ll> used;
		
		for (ll tmp = rhs.a; tmp >= 1; tmp >>= 1) {
			used.emplace(tmp);
		}

		for (ll tmp = rhs.b; tmp >= 1; tmp >>= 1) {
			if (used.count(tmp)) {
				rhs.lca = tmp;
				break;
			}
		}

		return in;
	}

};

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<Query> q(n);
	in >> q;
	std::unordered_map<pll, ll> edges;
	for (const auto& it : q) {
		if (it.type == 1) {
			for (ll tmp = it.a; tmp > it.lca; tmp >>= 1) {
				const ll next = tmp >> 1;
				edges[{tmp, next}] += it.cost;
			}
			for (ll tmp = it.b; tmp > it.lca; tmp >>= 1) {
				const ll next = tmp >> 1;
				edges[{tmp, next}] += it.cost;
			}
			continue;
		}
		ll ans = 0;

		for (ll tmp = it.a; tmp > it.lca; tmp >>= 1) {
			const ll next = tmp >> 1;
			ans += edges[{tmp, next}];
		}
		for (ll tmp = it.b; tmp > it.lca; tmp >>= 1) {
			const ll next = tmp >> 1;
			ans += edges[{tmp, next}];
		}

		out << ans << endl;
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

