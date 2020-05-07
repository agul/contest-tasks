#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int pop_element(multiset<int>& a, const int order) {
	int ret = (order == 1 ? *a.begin() : *a.rbegin());
	a.erase(a.find(ret));
	return ret;
}

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	vector<pii> last(n, { -1, -1 });
	int mx = -1;
	for (int i = 0; i < m; ++i) {
		int x, y;
		io >> x >> y;
		--y;
		umax(mx, y);
		last[y] = { i, x - 1 };
	}
	multiset<int> val;
	int order = 0;
	for (int i = 0; i <= mx; ++i) {
		val.insert(a[i]);
	}
	vector<int> ans(n);
	for (int i = mx + 1; i < n; ++i) {
		ans[i] = a[i];
	}
	int last_index = 0;
	for (int i = mx; i >= 0; --i) {
		int cur = last[i].X;
		int type = last[i].Y;
		if (cur < last_index) {
			ans[i] = pop_element(val, order);
		}
		else {
			if (type != order) {
				order ^= 1;
			}
			ans[i] = pop_element(val, order);
			last_index = cur;
		}
	}
	for (const auto& it : ans) {
		io << it << ' ';
	}
	io << endl;
}
