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

inline bool check(const int p, const int r, const int s) {
	const int n = r + p + s;
	return max({ abs(r - s), abs(r - p), abs(p - s) }) == 1 && (n & (n - 1)) == 0 && n > 1;
}

std::string get_ans(const int p, const int r, const int s) {
	if (!check(p, r, s)) {
		return "";
	}
	if (p == 1 && r == 1 && s == 0) {
		return "PR";
	}
	if (p == 1 && r == 0 && s == 1) {
		return "PS";
	}
	if (p == 0 && r == 1 && s == 1) {
		return "RS";
	}
	const int n = p + r + s;
	if (n % 3 == 1) {
		return get_ans(p / 2 + p % 2, r / 2, s / 2)
			+ get_ans(p / 2, r / 2 + r % 2, s / 2)
			+ get_ans(p / 2, r / 2, s / 2 + s % 2);
	}
	return get_ans(p / 2 + p % 2, r / 2 + r % 2, s / 2)
		+ get_ans(p / 2 + p % 2, r / 2, s / 2 + s % 2)
		+ get_ans(p / 2, r / 2 + r % 2, s / 2 + s % 2);
}

void solve(istream& in, ostream& out) {
	input_txt();
	in >> __;
	for (int _ = 1; _ <= __; ++_) {
		std::cerr << _ << std::endl;
		out << "Case #" << _ << ": ";
		int n, r, p, s;
		in >> n >> r >> p >> s;
		std::string ans = get_ans(p, r, s);
		out << (ans.empty() ? "IMPOSSIBLE" : ans) << endl;
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

