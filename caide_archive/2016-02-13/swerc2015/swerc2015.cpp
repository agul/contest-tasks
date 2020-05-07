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
		ins >> n;
		vector<ll> a(n);
		for (int i = 0; i < n; ++i) {
			ins >> a[i];
		}
		sort(all(a), greater<ll>());
		ll ans = 0;
		for (int i = 0; i < n; ++i) {
			ans += a[i] * (i + 1);
		}
		ans -= a[n - 1];
		out << ans << endl;
	}
}
