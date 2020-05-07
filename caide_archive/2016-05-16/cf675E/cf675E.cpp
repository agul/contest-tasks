#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

ll col[MAXN * 4], add[MAXN * 4];

void push(int v) {
	if (col[v] != 0) {
		col[v * 2] = col[v * 2 + 1] = col[v];
		add[v * 2] = add[v * 2 + 1] = add[v];
		col[v] = 0;
		add[v] = 0;
	}
	if (add[v] != 0) {
		add[v * 2] += add[v];
		add[v * 2 + 1] += add[v];
		add[v] = 0;
	}
}

void assign(int v, int tl, int tr, int l, int r, int color) {
	if (l > r)
		return;
	if (l == tl && tr == r) {
		col[v] = color;
		add[v] = 0;
	}
	else {
		push(v);
		int tm = (tl + tr) / 2;
		assign(v * 2, tl, tm, l, min(r, tm), color);
		assign(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, color);
	}
}

void inc(int v, int tl, int tr, int l, int r, int delta) {
	if (l > r)
		return;
	if (l == tl && tr == r)
		add[v] += delta;
	else {
		push(v);
		int tm = (tl + tr) / 2;
		assign(v * 2, tl, tm, l, min(r, tm), delta);
		assign(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, delta);
	}
}

ll get(int v, int tl, int tr, int l, int r) {
	if (l > r)
		return 0;
	if (tl == l && tr == r)
		return (col[v] + add[v]) * (tr - tl + 1);
	int tm = (tl + tr) / 2;
	return get(v * 2, tl, tm, l, min(r, tm))
		+ get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<int> a(n - 1);
	for (auto& it : a) {
		io >> it;
	}
	fill(col, 0);
	fill(add, 0);
	ll ans = 0;
	for (int i = n - 1; i > 0; --i) {
		inc(1, 1, n, i + 1, n, 1);
		assign(1, 1, n, i + 1, a[i - 1], 1);
		ans += get(1, 1, n, i + 1, n);
	}
	io << ans << endl;
}
