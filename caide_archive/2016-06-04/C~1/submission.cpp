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

const int DX[] = { -1, 0, 1, 0, -1, -1, 1, 1};
const int DY[] = { 0, 1, 0, -1, -1, 1, 1, -1};

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

using Field = std::vector<std::string>;

bool check(const Field& a, const Field& b) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (a[i][j] != '?' && a[i][j] != b[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void dfs(Field& a, int v, int pos) {
	int x = v / 3;
	int y = v % 3;
	a[x][y] = pos + '0';
	for (int dir = 0; dir < 4; ++dir) {
		int nx = x + DX[dir];
		int ny = y + DY[dir];
		if (nx < 0 || nx > 2 || ny < 0 || ny > 2 || a[nx][ny] != '0') {
			continue;
		}
		dfs(a, nx * 3 + ny, pos + 1);
		return;
	}
}

bool go(const Field& a, Field& b, int x, int y) {
	b = Field(3, std::string(3, '0'));
	--x, --y;
	b[1][1] = '1';
	b[x / 3][x % 3] = '2';
	dfs(b, y, 3);
	return check(a, b);
}

void solve(istream& in, ostream& out) {
	Field a(3);
	in >> a;
	Field b;
	if (go(a, b, 4, 7) || go(a, b, 4, 1) || go(a, b, 2, 1) || go(a, b, 2, 3) || go(a, b, 6, 3) || go(a, b, 6, 9) || go(a, b, 8, 7) || go(a, b, 8, 9)) {
		for (const auto& it : b) {
			out << it << endl;
		}
		return;
	}
	else {
		assert(false);
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

