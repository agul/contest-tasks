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

void solve(std::istream& in, std::ostream& out) {
	std::string s;
	in >> s;
	int x = s.find('.');
	int y = s.find('e');
	int deg = 0;
	if (y != std::string::npos) {
		deg = std::stoi(s.substr(y + 1));
		s = s.substr(0, y);
	}
	if (x == std::string::npos) {
		s += '.';
		x = s.length() - 1;
	}
	std::string a = s.substr(0, x);
	std::string b = s.substr(x + 1);
	if (deg > 0) {
		if (b.length() <= deg) {
			a += b;
			deg -= b.length();
			b = "";
			a += std::string(deg, '0');
		}
		else {
			a += b.substr(0, deg);
			b = b.substr(deg);
		}
	}
	else {
		deg = abs(deg);
		if (a.length() <= deg) {
			b = a + b;
			deg -= a.length();
			a = std::string(deg, '0');
			b = a + b;
			a = "";
		}
		else {
			b = a.substr(a.length() - deg) + b;
			a = a.substr(0, a.length() - deg);
		}
	}
	while (!b.empty() && b.back() == '0') {
		b.pop_back();
	}
	while (!a.empty() && a.front() == '0') {
		a.erase(a.begin());
	}
	if (a.empty()) {
		a = "0";
	}
	assert(a == "8549");
	out << a;
	if (!b.empty()) {
		out << "." << b;
	}
	out << endl;

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

