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

constexpr const int DX[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
constexpr const int DY[] = { 0, 1, 0, -1, -1, 1, 1, -1 };

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

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

namespace std {

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
	for (auto& it : vec) {
		in >> it;
	}
	return in;
}

}

#include <iterator>

using namespace std;

void output(const vector<string>& a, ostream& out) {
	for (const auto& it : a) {
		out << it << endl;
	}
}

std::vector<std::string> process(const vector<string>& a) {
	int n = a.size();
	int m = a.front().size();
	vector<string> b = a;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] != 'O') {
				continue;
			}
			b[i][j] = 'O';
			for (int dir = 0; dir < 4; ++dir) {
				int nx = i + DX[dir];
				int ny = j + DY[dir];
				if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
					continue;
				}
				b[nx][ny] = 'O';
			}
		}
	}
	auto xored = a;
	bool any = false;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			xored[i][j] = (b[i][j] == 'O' ? '.' : 'O');
		}
	}
	return xored;
}

void solve(std::istream& in, std::ostream& out) {
	int n, m, steps;
	in >> n >> m >> steps;
	vector<string> a(n);
	in >> a;
	--steps;
	auto xored = process(a);
	if (steps == 0) {
		output(a, out);
		return;
	}
	if (steps % 4 == 0) {
		output(process(xored), out);
		return;
	}
	if (steps % 4 == 1 || steps % 4 == 3) {
		for (auto& row : a) {
			for (auto& cell : row) {
				cell = 'O';
			}
		}
		output(a, out);
		return;
	}
	output(xored, out);
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

