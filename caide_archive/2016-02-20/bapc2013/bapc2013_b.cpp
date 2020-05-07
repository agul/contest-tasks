#include "Head.h"
#include "IO/IO.h"
#include "DSU.h"
#include "Maths.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111;

double prob[1 << 16], nprob[1 << 16];
int sum[1 << 16];

void solve(istream& ins, ostream& out) {
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		int n, k, money;
		io >> n >> k >> money;
		vector<pii> a;
		for (int i = 0; i < n; ++i) {
			int x, y;
			io >> x >> y;
			a.emplace_back(x, y);
		}
		const int max_mask = 1 << n;
		for (int mask = 0; mask < max_mask; ++mask) {
			prob[mask] = 1;
			nprob[mask] = 1;
			sum[mask] = 0;
			for (int i = 0; i < n; ++i) {
				if (mask & (1 << i)) {
					sum[mask] += a[i].X;
					prob[mask] *= a[i].Y / 100.;
					nprob[mask] *= (100 - a[i].Y) / 100.;
				}
			}
		}
		double ans = 0;
		for (int mask = 0; mask < max_mask; ++mask) {
			if (popcount(mask) != k) {
				continue;
			}
			int rev = (max_mask - 1) ^ mask;
			for (int sub_mask = rev; ; sub_mask = (sub_mask - 1) & rev) {
				if (sum[mask] + sum[sub_mask] <= money) {
					ans += prob[mask] * nprob[sub_mask];
				}
				if (sub_mask == 0) {
					break;
				}
			}
		}
		out << fixed << setprecision(16) << ans << endl;
	}
}
