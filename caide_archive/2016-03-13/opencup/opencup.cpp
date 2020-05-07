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
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	sort(all(a));
	int ans = 0;
	int cur_ind = 0;
	while (cur_ind < n) {
		int y = cur_ind;
		while (y < n && a[y] == a[cur_ind]) {
			++y;
		}
		umax(ans, y - cur_ind);
		cur_ind = y;
	}
	io << ans << endl;
}
