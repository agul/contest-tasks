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

const int MAXN = 111111;

void go(const std::vector<int>& last, const std::vector<int>& lis, const int n, std::vector<int>& ans, int& cur_index) {
	const int to = last[n];
	if (to == 0) {
		std::vector<int> tmp;
		for (int i = 0; i < n; ++i) {
			tmp.emplace_back(++cur_index);
		}
		std::reverse(all(tmp));
		ans.insert(ans.end(), all(tmp));
		return;
	}
	go(last, lis, to, ans, cur_index);
	if (n - to == 1) {
		std::vector<int> tmp;
		for (int i = 0; i < lis[to]; ++i) {
			tmp.emplace_back(++cur_index);
		}
		ans.insert(ans.begin(), all(tmp));
		return;
	}
	const int div = n / to;
	std::vector<int> tmp;
	for (int i = 0; i < div; ++i) {
		tmp.emplace_back(++cur_index);
	}
	std::reverse(all(tmp));
	ans.insert(ans.end(), all(tmp));
}

void solve(istream& in, ostream& out) {
	std::vector<int> lis(MAXN, 1);
	std::vector<int> dp(MAXN);
	vector<int> last(MAXN, 0);
	std::iota(all(dp), 0);
	for (int i = 6; i < MAXN; ++i) {
		for (int div = 2; div * div <= i; ++div) {
			if (i % div != 0) {
				continue;
			}
			int val = dp[i / div] + div;
			int ls = lis[i / div] + 1;
			if (val < dp[i] || (val == dp[i] && ls < lis[i])) {
				dp[i] = val;
				lis[i] = ls;
				last[i] = i / div;
			}
		}

		int val = dp[i - 1] + lis[i - 1];
		int ls = lis[i - 1];
		if (val < dp[i] || (val == dp[i] && ls < lis[i])) {
			dp[i] = val;
			lis[i] = ls;
			last[i] = i - 1;
		}
	}
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		int n;
		in >> n;
		std::vector<int> ans;
		int cur_index = 0;
		go(last, lis, n, ans, cur_index);
		out << ans.size() << endl;
		for (const auto& it : ans) {
			out << it << " ";
		}
		out << endl;
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

