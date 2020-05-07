#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, t, k;
	in >> n >> t >> k;
	for (int i : range(n)) {
		int m;
		in >> m;
		vector<int> a(m);
		in >> a;
		int ans = 0;
		int sum = 0;
		int mx = 0;
		for (int j : range(m)) {
			sum += a[j];
			umax(mx, a[j]);
			int cur = sum - mx + min(k, mx);
			if (cur > t) {
				break;
			}
			++ans;
		}
		out << ans << endl;
	}
}
