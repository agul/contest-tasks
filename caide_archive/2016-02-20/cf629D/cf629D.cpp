#include "Head.h"
#include "IO/IO.h"
#include "SegmentTree.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int p[MAXN];
ll wh[MAXN];

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<pair<ll, int>> a(n);
	for (int i = 0; i < n; ++i) {
		ll r, h;
		io >> r >> h;
		ll v = sqr(r) * h;
		a[i] = { v, i };
	}
	sort(all(a));
	int cur_ind = 0;
	int cnt = 0;
	while (cur_ind < n) {
		int y = cur_ind;
		while (y < n && a[cur_ind].X == a[y].X) {
			++y;
		}
		wh[cnt] = a[cur_ind].X;
		for (; cur_ind < y; ++cur_ind) {
			p[a[cur_ind].Y] = cnt;
		}
		++cnt;
	}
	SegmentTreeCmp<ll> tree(cnt, greater<ll>(), 0);
	tree.init();
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		int pr = p[i] - 1;
		ll cur_max;
		if (pr >= 0) {
			cur_max = tree.query(0, pr);
		}
		else {
			cur_max = 0;
		}
		ll new_max = cur_max + wh[p[i]];
		tree.update(p[i], new_max);
		umax(ans, new_max);
	}
	out << fixed << setprecision(16) << ans * PI << endl;
}
