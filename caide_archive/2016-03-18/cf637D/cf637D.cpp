#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n, m, s, d;
	io >> n >> m >> s >> d;
	vector<int> a(n);
	for (auto& it : a) {
		io >> it;
	}
	sort(all(a));
	int last = a[0];
	vector<pii> b;
	bool fst = true;
	for (int i = 0; i < n; ++i) {
		if (fst || a[i] - last >= s + 2) {
			b.emplace_back(a[i], a[i]);
			fst = false;
		} else {
			b.back().Y = a[i];
		}
		last = a[i];
	}
	vector<pii> ans;
	bool ok = true;
	int last_pos = 0;
	for (const auto& it : b) {
		if (last_pos >= it.X || it.Y - it.X > d - 2) {
			ok = false;
			break;
		}
		ans.emplace_back(0, it.X - 1 - last_pos);
		last_pos = it.Y + 1;
		ans.emplace_back(1, last_pos - it.X + 1);
	}
	if (last_pos != m) {
		ans.emplace_back(0, m - last_pos);
	}
	if (!ok) {
		io << "IMPOSSIBLE" << endl;
		return;
	}
	for (const auto& it : ans) {
		io << (it.X ? "JUMP" : "RUN") << ' ' << it.Y << endl;
	}
}
