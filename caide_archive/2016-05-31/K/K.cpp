#include "Head.h"
#include "Graph/graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 222222;


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
