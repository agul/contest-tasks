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

#ifdef _MSC_VER

#endif

using namespace std;

void solve(istream& in, ostream& out) {
	/* unordered_set<string> a;
	string s, t;
	in >> s >> t;
	for (int i = 1; i <= s.length(); ++i) {
		for (int j = 0; j < t.length(); ++j) {
			std::string tmp = s.substr(0, i) + t.substr(j);
			if (a.count(tmp)) {
				out << "DUPLICATE: " << tmp << endl;
			}
			a.emplace(tmp);
		}
	}
	out << a.size() << endl; */
	std::string s, t;
	in >> s >> t;
	vector<int> cnt(256, 0);
	for (const auto& it : t) {
		++cnt[it];
	}
	--cnt[t.back()];
	ll ans = static_cast<ll>(s.length()) * t.length();
	for (const auto& it : s) {
		ans -= cnt[it];
	}
	ans += cnt[s.front()];
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

