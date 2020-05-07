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

const int INF = 0x3f3f3f3f;

template<class T> 
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

#ifdef _MSC_VER

#endif

using namespace std;

void solve(istream& in, ostream& out) {
	int ls, n;
	string s;
	in >> ls >> n >> s;
	vector<pair<string, int>> actors(n);
	for (auto& it : actors) {
		int x;
		in >> x >> it.second >> it.first;
	}
	vector<int> dp(ls + 1, INF);
	dp[0] = 0;
	for (int i = 1; i <= ls; ++i) {
		for (int j = 0; j < i; ++j) {
			const int len = i - j;
			const std::string sub = s.substr(j, len);
			int cost = INF;
			for (const auto& it : actors) {
				if (it.first.find(sub) != std::string::npos) {
					umin(cost, it.second);
				}
			}
			if (cost == INF) {
				continue;
			}
			umin(dp[i], dp[j] + len * cost);
		}
	}
	out << (dp[ls] == INF ? -1 : dp[ls]) << endl;
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

