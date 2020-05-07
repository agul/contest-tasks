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

#include <iterator>

using namespace std;

void output(std::ostream& out, const std::string& a, const std::string& b, int deg) {
	assert(a.length() == 1);
	assert(a.front() >= '1' && a.front() <= '9');
	out << a;
	if (!b.empty()) {
		out << "." << b;
	}
	if (deg != 0) {
		out << "E" << deg;
	}
	out << endl;
}

void solve(std::istream& in, std::ostream& out) {
	string s, a, b;
	in >> s;
	const int len = s.length();
	int cur_ind = 0;
	while (cur_ind < len && s[cur_ind] != '.') {
		a += s[cur_ind];
		++cur_ind;
	}
	++cur_ind;
	while (cur_ind < len) {
		b += s[cur_ind];
		++cur_ind;
	}

	while (!b.empty() && b.back() == '0') {
		b.pop_back();
	}
	if (a.empty()) {
		a = "0";
	}

	int deg = 0;
	
	int zero = 0;
	while (zero < a.length() && a[zero] == '0') {
		++zero;
	}
	if (zero >= a.length()) {
		int index = 0;
		while (index < b.length() && b[index] == '0') {
			++index;
		}
		a = b.substr(index, 1);
		b = b.substr(index + 1);
		output(out, a, b, -(index + 1));
		return;
	}
	a = a.substr(zero);

	if (a.length() > 1) {
		deg += a.length() - 1;
		b = a.substr(1) + b;
		a = a.substr(0, 1);
	}

	while (!b.empty() && b.back() == '0') {
		b.pop_back();
	}

	output(out, a, b, deg);

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

