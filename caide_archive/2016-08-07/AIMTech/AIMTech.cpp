#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, b, d;
	in >> n >> b >> d;
	vector<int> a(n);
	in >> a;
	int ans = 0;
	int cur_sum = 0;
	for (int i : range(n)) {
		cur_sum += a[i];
		if (cur_sum > d) {
			++ans;
			cur_sum = 0;
		}
	}
	out << ans << endl;
}
