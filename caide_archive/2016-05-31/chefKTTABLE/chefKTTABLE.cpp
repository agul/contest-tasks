#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		int n;
		in >> n;
		vector<int> a(n), b(n);
		in >> a >> b;
		a.insert(a.begin(), 0);
		b.insert(b.begin(), 0);
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			const int timedelta = a[i] - a[i - 1];
			if (b[i] <= timedelta) {
				++ans;
			}
		}
		out << ans << endl;
	}
}
