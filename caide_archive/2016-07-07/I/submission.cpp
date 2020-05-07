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

vector<pair<int, int>> a(555555);
int s = 0;

void ans(int l, int r) {
	if (l == r)
		return;
	if (r - l == 1) {
		a[s++] = make_pair(l, r);
		return;
	}
	if ((r - l + 1) & 1) {
		a[s++] = make_pair(l, r - 1);
		ans(l + (r - l) / 2, r);
		a[s++] = make_pair(l, r - 1);
	}
	else {
		a[s++] = make_pair(l, l + 1);
		ans(l + 1, r);
		a[s++] = make_pair(l, l + 1);
	}
}

void solve(std::istream& in, std::ostream& out) {
	int __;
	in >> __;
	for (int _ = 0; _ < __; _++) {
		s = 0;
		int n;
		in >> n;
		vector<int> b(n);
		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			int k;
			in >> k;
			k--;
			b[i] = k;
			v[k] = i;
		}
		for (int i = n - 1; i > 0; i--) {
			if (v[i] < i) {
				ans(v[i], i);
				int k = v[i], p = b[i];
				v[i] = i;
				b[i] = i;
				b[k] = p;
				v[p] = k;
			}
		}
		out << s<<endl;
		for (int i = 0; i < s; i++) {
			out << a[i].first+1 << ' ' << a[i].second+1 << endl;
		}
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

