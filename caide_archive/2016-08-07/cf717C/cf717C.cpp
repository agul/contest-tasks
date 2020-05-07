#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<ll> a(n);
	in >> a;
	sort(a);
	ll ans = 0;
	for (int i : range(n)) {
		ans += a[i] * a[n - 1 - i];
	}
	ans %= 10007;
	out << ans << endl;
}
