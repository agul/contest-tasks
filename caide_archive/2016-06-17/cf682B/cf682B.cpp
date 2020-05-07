#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<int> a(n);
	in >> a;
	sort(a);
	int ans = 0;
	for (int i = 1, cur_ind = 0; i <= n; ++i, ++cur_ind) {
		while (cur_ind < n && a[cur_ind] < i) {
			++cur_ind;
		}
		if (cur_ind == n) {
			break;
		}
		ans = i + 1;
	}
	out << ans << endl;
}
