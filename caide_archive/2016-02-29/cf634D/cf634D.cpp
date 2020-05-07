#include "Head.h"
#include "IO/IO.h"
#include "Stack.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int d, v, n;
	io >> d >> v >> n;
	vector<pii> a;
	a.emplace_back(0, 0);
	a.emplace_back(d, 0);
	for (int i = 0; i < n; ++i) {
		int x, y;
		io >> x >> y;
		a.emplace_back(x, y);
	}
	sort(all(a));
	for (int i = 1; i < a.size(); ++i) {
		if (a[i].X - a[i - 1].X > v) {
			io << -1 << endl;
			return;
		}
	}
	vector<int> nxt(a.size());
	Stack<pii> st(a.size());
	for (int i = 0; i < a.size(); ++i) {
		while (!st.empty() && a[i].Y <= st.top().X) {
			nxt[st.pop().Y] = i;
		}
		st.push({ a[i].Y, i });
	}
	int pos = 0;
	ll ans = 0;
	int cur_ind = 1;
	int last_pos = 0;
	int cur_vol = v;
	int beg = 0;
	while (pos < a.size() - 1) {
		cur_vol -= a[pos].X - last_pos;
		last_pos = a[pos].X;
		auto& it = a[nxt[pos]];
		int new_vol = cur_vol;
		int new_pos = pos;
		if (it.X - a[pos].X > v || it.Y > a[pos].Y) {
			new_vol = v;
			new_pos = pos + 1;
		}
		else {
			new_vol = max(cur_vol, it.X - a[pos].X);
			new_pos = nxt[pos];
		}
		ans += (ll)a[pos].Y * (new_vol - cur_vol);
		cur_vol = new_vol;
		pos = new_pos;
	}
	io << ans << endl;
}
