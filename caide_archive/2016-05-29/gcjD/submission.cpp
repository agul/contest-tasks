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

#define popcount(a) __popcnt(a)

#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#define all(a) a.begin(), a.end()

const int INF = 0x3f3f3f3f;

template<class T> 
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

#ifdef _MSC_VER

#endif

  // namespace std

extern bool local_input;
extern bool local_output;

void input_txt() {
	if (!local_input) {
		freopen("input.txt", "r", stdin);
	}
	if (!local_output) {
		freopen("output.txt", "w", stdout);
	}
}

using namespace std;

int __;

bool workday(const std::vector<int>& a, const std::vector<int>& order, std::vector<bool>& used, const int pos) {
	const int n = a.size();
	if (pos == n) {
		return true;
	}
	bool worked = false;
	for (int i = 0; i < n; ++i) {
		if ((a[order[pos]] & (1 << i)) && !used[i]) {
			used[i] = true;
			if (!workday(a, order, used, pos + 1)) {
				return false;
			}
			used[i] = false;
			worked = true;
		}
	}
	return worked;
}

bool check(const std::vector<int>& a) {
	const int n = a.size();
	std::vector<int> order(n);
	std::iota(all(order), 0);
	bool ok = true;
	do {
		vector<bool> used(n, false);
		ok &= workday(a, order, used, 0);
	} while (next_permutation(all(order)));
	return ok;
}

int go(std::vector<int>& a, const int pos) {
	const int n = a.size();
	if (pos == n) {
		return check(a) ? 0 : INF;
	}
	const int init = a[pos];
	int ret = INF;
	for (int mask = 0; mask < (1 << n); ++mask) {
		if ((mask & init) != init) {
			continue;
		}
		if (mask == 2) {
			mask = 2;
		}
		if (mask == 6) {
			mask = 6;
		}
		const int cur = popcount(mask ^ init);
		a[pos] = mask;
		const int value = go(a, pos + 1);
		umin(ret, cur + value);
	}
	a[pos] = init;
	return ret;
}

int solve(std::vector<int>& a) {
	return go(a, 0);
}

void solve(istream& in, ostream& out) {
	input_txt();
	in >> __;
	for (int _ = 1; _ <= __; ++_) {
		std::cerr << _ << std::endl;
		out << "Case #" << _ << ": ";
		int n;
		in >> n;
		vector<int> a(n);
		for (int i = 0; i < n; ++i) {
			std::string s;
			in >> s;
			int cur = 0;
			for (int j = 0; j < n; ++j) {
				cur = (cur << 1) ^ (s[j] == '1' ? 1 : 0);
			}
			a[i] = cur;
		}
		int ans = solve(a);
		out << ans << endl;
	}
}

#include <fstream>

bool local_input;
bool local_output;

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;
    local_input = false;

    ostream& out = cout;
    local_output = false;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}

