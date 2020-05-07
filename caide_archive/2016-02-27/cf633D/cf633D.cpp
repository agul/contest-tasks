#include "Head.h"
#include "IO/IO.h"
#include "HashMap.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

oaht::hash_map<int, int> cnt, cur_map;

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<int> a(n);
	cnt.clear();
	int cnt_zero = 0;
	for (int i = 0; i < n; ++i) {
		io >> a[i];
		++cnt[a[i]];
		cnt_zero += (a[i] == 0 ? 1 : 0);
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				continue;
			}
			int cur = 2;
			ll x = a[i], y = a[j];
			if (x == 0 && y == 0) {
				umax(ans, cnt_zero);
				continue;
			}
			cur_map.clear();
			cur_map[x]++;
			cur_map[y]++;
			for (;;) {
				int nxt = x + y;
				int val = ++cur_map[nxt];
				if (cnt.count(nxt) && val <= cnt[nxt]) {
					++cur;
					x = y;
					y = nxt;
				}
				else {
					break;
				}
			}
			umax(ans, cur);
		}
	}
	io << ans << endl;
}
