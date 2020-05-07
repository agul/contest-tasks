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
	template<typename... Args,
		typename R = std::vector<decltype(MakeVector<T, N - 1>::make_vector(std::declval<Args>()...)) >>
		static R make_vector(size_t first, Args... sizes) {
		auto inner = MakeVector<T, N - 1>::make_vector(sizes...);
		return R(first, inner);
	}
};

template<typename T>
struct MakeVector<T, 1> {
	/// caide keep
	template<typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

template<typename T, typename... Args>
auto make_vector(Args... args) -> decltype(MakeVector<T, sizeof...(Args)-1>::make_vector(args...)) {
	return MakeVector<T, sizeof...(Args)-1>::make_vector(args...);
}

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#define pii std::pair<int, int>

#include <iterator>

inline int dig(const char ch)
// get exact numeric value of the corresponding char
// REQUIRE: char from '0' to '9'
{
	return ch - '0';
}

using namespace std;

void solve(std::istream& in, std::ostream& out) {
	auto keys = make_vector<int>(4, 3, 0);
	int cnt = 1;
	for (auto& row : keys) {
		for (auto& cell : row) {
			cell = cnt++;
		}
	}
	keys[3][1] = 0;
	std::vector<pii> but(10);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			const int cell = keys[i][j]; 
			if (cell > 9) {
				continue;
			}
			but[cell] = { i, j };
		}
	}
	std::string s;
	int n;
	in >> n >> s;
	std::vector<pii> pos;
	for (const auto& ch : s) {
		const int x = dig(ch);
		pos.emplace_back(but[x]);
	}
	for (int dir = 0; dir < 4; ++dir) {
		bool ok = true;
		for (const auto& it : pos) {
			int nx = it.first + DX[dir];
			int ny = it.second + DY[dir];
			if (nx < 0 || ny < 0 || nx >= 4 || ny >= 3 || keys[nx][ny] > 9) {
				ok = false;
				break;
			}
		}
		if (ok) {
			out << "NO" << endl;
			return;
		}
	}
	out << "YES" << endl;
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

