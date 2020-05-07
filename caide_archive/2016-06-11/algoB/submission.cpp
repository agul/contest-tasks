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

const int INF = 0x3f3f3f3f;

template<class T> 
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
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

using namespace std;

int ans;
vector<int> a, divs, vec, best;

ll get(ll val) {
	ll res = 0;
	reverse(all(vec));
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i] > val) {
			continue;
		}
		res += val / vec[i];
		val %= vec[i];
	}
	reverse(all(vec));
	return res;
}

ll get_fast() {
	ll res = 0;
	for (const auto& it : a) {
		res += get(it);
	}
	return res;
}

void go(const int pos) {
	bool any = false;
	for (int i = pos + 1; i < divs.size(); ++i) {
		if (divs[i] % divs[pos] == 0) {
			any = true;
			vec.emplace_back(divs[i]);
			go(i);
			vec.pop_back();
		}
	}
	if (!any) {
		const int cur = get_fast();
		if (umin(ans, cur)) {
			best = vec;
		}
	}
}

void solve(istream& in, ostream& out) {
	int n;
	in >> n;
	a.resize(n);
	in >> a;

	sort(all(a));
	ans = INF;
	for (const auto& it : a) {
		divs.clear();
		for (int i = 1; i <= it; ++i) {
			if (it % i == 0) {
				divs.emplace_back(i);
			}
		}
		vec = { 1 };
		go(0);
	}
	out << ans << endl;
	return;
	for (const auto& it : best) {
		out << it << " ";
	}
	out << endl;

	/* for (int test = 0; test < 100; ++test) {
		int n = Random::get(1, 7);
		a.resize(n);
		for (int i = 0; i < n; ++i) {
			a[i] = Random::get(1, 100);
		}
		sort(all(a));
		out << "Test #" << test << ": " << n << endl;
		for (const auto& it : a) {
			out << it << " ";
		}
		out << endl;
		ans = INF;
		divs = { 1 };
		vec = { 1 };
		for (const auto& it : a) {
			for (int i = 2; i <= it; ++i) {
				if (it % i == 0) {
					divs.emplace_back(i);
				}
			}
		}
		sort(all(divs));
		divs.resize(unique(all(divs)) - divs.begin());
		go(0);
		out << ans << endl;
		for (const auto& it : best) {
			out << it << " ";
		}
		out << endl << endl;
	} */
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

