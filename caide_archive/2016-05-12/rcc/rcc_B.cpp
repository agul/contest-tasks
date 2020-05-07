#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		int n;
		ll h;
		io >> n >> h;
		vector<int> a(n);
		for (auto& it : a) {
			io >> it;
		}
		vector<int> col(n);
		for (auto& it : col) {
			io >> it;
		}
		int ans = 0;
		ll len = 0;
		int sum = 0;
		int cur_ind = 0;
		if (col[0] == 0) {
			++ans;
			col[0] = 1;
		}
		for (int i = 0; i < n; ++i) {
			while (cur_ind < n && len < h) {
				sum += col[cur_ind];
				len += a[cur_ind];
				++cur_ind;
			}
			if (sum == 0) {
				col[cur_ind - 1] = 1;
				++sum;
				++ans;
			}
			sum -= col[i];
			len -= a[i];
		}

		io << ans << endl;
	}
}
