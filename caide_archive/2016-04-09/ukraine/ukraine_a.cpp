#include "Head.h"
#include "IO/IO.h"
#include "Maths.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void output(const std::vector<int>& ans) {
	for (const auto& it : ans) {
		io << it << endl;
	}
}

void solve(istream& ins, ostream& out) {
	int m, n;
	io >> m >> n;
	vector<pii> a(n);
	int x = -1, y = -1;
	int x_ind = -1, y_ind = -1;
	int cnt = 0;
	for (auto& it : a) {
		++cnt;
		io >> it.X >> it.Y;
		if (it.X == 2) {
			if (x == -1) {
				x = it.Y;
				x_ind = cnt;
			}
			else {
				y = it.Y;
				y_ind = cnt;
			}
		}
	}
	vector<int> ans;
	if (y == -1 || y > x_ind) {
		--x, --y;
		int L = 0, R = m;
		for (int i = 0; i < n; ++i) {
			if (a[i].X == 2) {
				R = m;
				continue;
			}
			int cur_place = L;
			if (i == x || i == y) {
				R -= a[i].Y;
				cur_place = R;
			}
			else {
				L += a[i].Y;
			}
			if (L > m || cur_place < 0 || (cur_place < L && (i == x || i == y)) || (cur_place >= R && i != x && i != y)) {
				io << "IMPOSSIBLE" << endl;
				return;
			}
			ans.emplace_back(cur_place);
		}
		output(ans);
		return;
	}
	--x, --y;
	int y_place = m - a[y].Y, x_place = y_place - a[x].Y;
	int L = 0, R = x_place;
	for (int i = 0; i < n; ++i) {
		if (a[i].X == 2) {
			R += a[a[i].Y - 1].Y;
			continue;
		}
		int cur_place = L;
		if (i == x) {
			cur_place = x_place;
		}
		else 
		if (i == y) {
			cur_place = y_place;
		}
		else {
			L += a[i].Y;
		}
		if (L > m || cur_place < 0 || (cur_place < L && (i == x || i == y)) || (cur_place >= R && i != x && i != y)) {
			io << "IMPOSSIBLE" << endl;
			return;
		}
		ans.emplace_back(cur_place);
	}
	output(ans);
}
