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

struct Ans {
	int t = 0;
	int index = 0;
	int v = 0;
	int e = 0;
};

struct Edge {
	int a = 0;
	int b = 0;
	int p = 0;
};

bool cmp_edge(Edge a, Edge b) {
	return a.p < b.p;
}
bool cmp_1(Ans a, Ans b) {
	return a.t < b.t;
}
bool cmp_2(Ans a, Ans b) {
	return a.index < b.index;
}

void solve(std::istream& in, std::ostream& out) {
	int n, m, a, b, p, q;
	in >> n >> m;
	vector<int> v(n, 0);
	vector<Edge> e(m);
	for (int i = 0; i < m; i++) {
		in >> a >> b >> p;
		a--; b--;
		e[i].a = a;
		e[i].b = b;
		e[i].p = p;
		v[a]++; v[b]++;
	}
	int count[5] = { 0,0,0,0,0 };
	int edge = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] > 2) {
			count[3]++;
			edge += v[i];
		}
		else count[v[i]]++;
	}
	for (int i = 0; i < n; i++) {
		if (v[i] > 2)count[3]++;
		else count[v[i]]++;
	}
	sort(e.begin(), e.end(), cmp_edge);
	in >> q;
	vector<Ans> rec(q);
	for (int i = 0; i < q; i++) {
		in >> rec[i].t; rec[i].index = i;
	}
	sort(rec.begin(), rec.end(), cmp_1);
	int l = 0;
	for (int i = 0; i < q; i++) {
		while ((l < m) && (e[l].p < rec[i].t)) {
			if (v[e[l].a] <= 3) {
				count[v[e[l].a]]--;
				count[v[e[l].a] - 1]++;
			}
			else edge--;
			v[e[l].a]--;

			if (v[e[l].b] <= 3) {
				count[v[e[l].b]]--;
				count[v[e[l].b] - 1]++;
			}
			else edge--;
			v[e[l].b]--;
			l++;
		}
		int vv = 0, ee =0;
		vv = count[1] + count[3];
		ee = (count[1] + edge)/2;
		rec[i].e = ee;
		rec[i].v = vv;
		cout << rec[i].index << ' ' << rec[i].t << ' ' << rec[i].e << ' ' << rec[i].v << endl;
	}
	sort(rec.begin(), rec.end(), cmp_2);
	for (int i = 0; i < q; i++) {
		cout << rec[i].v << ' ' << rec[i].e << endl;
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

