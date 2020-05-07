#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

const int DELTA[] = { 1, 0, -1 };

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n;
		in >> n;
		vector<ll> a(n), b(n);
		in >> b >> a;
		const ll sum = std::accumulate(all(a), 0LL) + std::accumulate(all(b), 0LL);
		if (sum % n != 0) {
			out << -1 << endl;
			continue;
		}
		const ll need = sum / n;
		if (n == 1) {
			out << need << endl;
			continue;
		}
		auto dp = make_vector<bool>(n + 1, 8, false);
		dp[0][0] = true;
		a.insert(a.begin(), 0);
		b.insert(b.begin(), 0);
		b.insert(b.end(), 0);
		for (int i : inclusiveRange(1, n)) {
			for (int mask : range(8)) {
				for (int prev_mask : range(8)) {
					const int prev = (prev_mask & 3) << 1;
					if (!dp[i - 1][prev_mask] || (mask | prev) != mask) {
						continue;
					}
					const int nmask = mask ^ prev;
					int val = a[i];
					for (int ind : range(3)) {
						if (nmask & (1 << ind)) {
							val += b[i + DELTA[ind]];
						}
					}
					dp[i][mask] = dp[i][mask] || (val == need);
				}
			}
		}
		out << (dp[n][6] ? need : -1) << endl;
	}
}
