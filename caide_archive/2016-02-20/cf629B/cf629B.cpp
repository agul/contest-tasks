#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<pii> men, women;
	for (int i = 0; i < n; ++i) {
		char ch;
		int x, y;
		io >> ch >> x >> y;
		(ch == 'M' ? men : women).emplace_back(x, y);
	}
	int ans = 0;
	for (int i = 1; i <= 366; ++i) {
		int mc = 0;
		int wc = 0;
		for (const auto& it : men) {
			if (it.X <= i && i <= it.Y) {
				++mc;
			}
		}
		for (const auto& it : women) {
			if (it.X <= i && i <= it.Y) {
				++wc;
			}
		}
		int cnt = min(mc, wc);
		umax(ans, cnt * 2);
	}
	io << ans << endl;
}
