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
		--a[i];
	}
	vector<int> ans(n, 0);
	for (int i = 0; i < n; ++i) {
		vector<int> cnt(n, 0);
		int best = 0;
		for (int j = i; j < n; ++j) {
			++cnt[a[j]];
			if (cnt[a[j]] > cnt[best] || (cnt[a[j]] == cnt[best] && a[j] < best)) {
				best = a[j];
			}
			++ans[best];
		}
	}
	for (int i = 0; i < n; ++i) {
		io << ans[i] << " ";
	}
	io << endl;
}
