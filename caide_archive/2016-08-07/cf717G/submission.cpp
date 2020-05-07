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

template<typename T>
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
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

namespace std {

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
	for (auto& it : vec) {
		in >> it;
	}
	return in;
}

template<typename T, typename U>
std::istream& operator>>(std::istream& in, std::pair<T, U>& rhs) {
	in >> rhs.first >> rhs.second;
	return in;
}

}

#include <iterator>

void prefixFunction(int p[], const char * s, int n = 0) {
	if (!n) {
		n = strlen(s);
	}
	p[0] = 0;
	for (int i = 1; i < n; ++i) {
		int j = p[i - 1];
		while (j && s[i] != s[j]) {
			j = p[j - 1];
		}
		if (s[i] == s[j]) {
			++j;
		}
		p[i] = j;
	}
}

void prefixFunction(int p[], const std::string& s) {
	prefixFunction(p, s.c_str(), s.length());
}

using namespace std;

const int MAXN = 777;

int prefix[MAXN];

void solve(std::istream& in, std::ostream& out) {
	int ls, n, x;
	string s;
	in >> ls >> s >> n;
	std::vector<pair<string, int>> a(n);
	in >> a >> x;
	std::vector<std::set<int>> pos(ls);
	for (int i = 0; i < n; ++i) {
		string tmp = a[i].first + "#" + s;
		prefixFunction(prefix, tmp);
		const int len = a[i].first.length();
		int start = len + 1;
		for (int index = start; index < tmp.length(); ++index) {
			if (prefix[index] == len) {
				pos[index - start].emplace(i);
			}
		}
	}
	ll ans = 0;
	for (int iter = 0; iter < x; ++iter) {
		vector<int> dp(ls + 1);
		vector<int> last(ls + 1);
		vector<int> mx(ls + 1);
		for (int i = 0; i < ls; ++i) {
			for (int j : pos[i]) {
				if (umax(dp[i + 1], dp[mx[i - a[j].first.length() + 1]] + a[j].second)) {
					last[i + 1] = j;
				}
			}
			mx[i + 1] = mx[i];
			if (dp[i + 1] > dp[mx[i + 1]]) {
				mx[i + 1] = i + 1;
			}
		}
		ans += dp[mx[ls]];
		int cur_pos = mx[ls];
		while (cur_pos > 0) {
			int xx = last[cur_pos];
			pos[cur_pos - 1].erase(last[cur_pos]);
			cur_pos -= a[xx].first.length();
			cur_pos = mx[cur_pos];
		}
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

