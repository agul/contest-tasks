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

#define ll int64_t

#ifdef _MSC_VER

#endif

using namespace std;

void solve(istream& in, ostream& out) {
	ll r, s, m, d, n, k, tmp, x, y, ans = 0;
	in >> r >> s >> m >> d >> n;
	vector<ll> b(r + 1);
	for (int i = 1; i <= r; i++) {
		in >> b[i];
	}
	vector<vector<ll> > ingr(s + m + d);
	for (int i = 0; i < s + m + d; i++) {
		in >> k;
		for (int j = 0; j < k; j++) {
			in >> tmp;
			ingr[i].push_back(tmp);
		}
	}
	vector<vector<bool> > v(s + m + d, vector<bool>(s + m + d, true));
	for (int i = 0; i < n; i++) {
		in >> x >> y;
		x--; y--;
		v[x][y] = false;
		v[y][x] = false;
	}
	for (int is = 0; is < s; is++) {
		for (int im = s; im < s + m; im++) {
			if (v[is][im]) {
				for (int id = s + m; id < s + m + d; id++) {
					if (v[is][id] && v[im][id]) {
						set<int> ingr_set;
						ll pre_ans = 1;
						for (int i = 0; i < ingr[is].size(); i++) {
							ingr_set.insert(ingr[is][i]);
						}
						for (int i = 0; i < ingr[im].size(); i++) {
							ingr_set.insert(ingr[im][i]);
						}
						for (int i = 0; i < ingr[id].size(); i++) {
							ingr_set.insert(ingr[id][i]);
						}
						for (auto& it : ingr_set) {
							if (pre_ans <= (ll)5e18 / b[it]) {
								pre_ans *= b[it];
							}
							else {
								out << "too many" << endl;
								return;
							}
						}
						ans += pre_ans;
						if (ans > (ll)1e18) {
							out << "too many" << endl;
							return;
						}
					}
				}
			}
		}
	}
	out << ans << endl;
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

