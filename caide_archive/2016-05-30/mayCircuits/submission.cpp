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

#ifdef _MSC_VER

#endif

using namespace std;

int __;

int calc(const std::string& s, const char ch) {
	int ans = 0;
	for (int i = 0; i < s.length(); ++i) {
		if (i + 1 < s.length() && s[i] == ch && s[i + 1] == ch) {
			++ans;
			++i;
		}
	}
	return ans;
}

void solve(istream& ins, ostream& out) {
	ins >> __;
	for (int _ = 0; _ < __; ++_) {
		int n;
		std::string s;
		ins >> n >> s;
		int ans = std::max(calc(s, 'B'), calc(s, 'G'));
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

