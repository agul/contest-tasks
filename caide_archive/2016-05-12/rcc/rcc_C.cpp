#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int get(const std::vector<int>& a, int div, bool f) {
	int res = -1;
	for (const auto& it : a) {
		if ((it % div == 0) == f) {
			if (res == -1) {
				res = it;
			}
			else {
				res = gcd(res, it);
			}
		}
	}
	return (res == -1 ? 1 : res);
}

void solve(istream& ins, ostream& out) {
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		int n;
		io >> n;
		vector<int> a(n);
		int mn = 0;
		for (int i = 0; i < n; ++i) {
			io >> a[i];
			if (a[i] < a[mn]) {
				mn = i;
			}
		}
		int ans = 1;
		for (int i = 1; i * i <= a[mn]; ++i) {
			umax(ans, min(get(a, i, 0), get(a, i, 1)));
			umax(ans, min(get(a, a[mn] / i, 0), get(a, a[mn] / i, 1)));
		}
		io << ans << endl;
	}
}
