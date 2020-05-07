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

#ifdef _MSC_VER

#endif

using namespace std;

int __;

void solve(istream& in, ostream& out) {
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		string s, t;
		in >> s >> t;
		int a = count(all(s), '1');
		int b = count(all(t), '1');
		if (a == s.length() || a == 0) {
			out << "Unlucky Chef" << endl;
			continue;
		}
		out << "Lucky Chef" << endl;
		if (a > b) {
			a = s.length() - a;
			b = s.length() - b;
			for (auto& it : s) {
				it ^= 1;
			}
			for (auto& it : t) {
				it ^= 1;
			}
		}
		int diff = b - a;
		int ans = diff;
		for (size_t i = 0; i < s.length() && diff > 0; ++i) {
			if (t[i] == '1' && s[i] == '0') {
				--diff;
				s[i] = '1';
			} 
		}
		for (size_t i = 0; i < s.length(); ++i) {
			if (t[i] == '0' && s[i] == '1') {
				++ans;
			}
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

