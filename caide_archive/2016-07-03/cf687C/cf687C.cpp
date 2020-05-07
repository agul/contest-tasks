#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 555;

using State = std::bitset<MAXN>;
using DP = std::vector<State>;

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	vector<int> a(n);
	in >> a;
	sort(a);
	DP dp(MAXN);
	dp[0][0] = 1;
	for (const auto& it : a) {
		for (int i = k - it; i >= 0; --i) {
			dp[i + it] |= dp[i];
			dp[i + it] |= (dp[i] << it);
		}
	}
	int cnt = dp[k].count();
	out << cnt << endl;
	for (int i = 0; i <= k; ++i) {
		if (dp[k][i]) {
			out << i << " ";
		}
	}
	out << endl;
}
