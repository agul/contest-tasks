#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

std::pair<double, double> d[MAXN][55];

void solve(istream& ins, ostream& out) {
	int n, k;
	io >> n >> k;
	vector<int> a(n);
	for (auto& it : a) {
		io >> it;
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= k; ++j) {
			d[i][j] = mp(LINF, LINF);
		}
	}
	d[0][1] = mp(0, 0);
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j <= min(i + 1, k); ++j) {
			for (int q = 0; q < 2; ++q) {
				if (q == 0) {
					double delta = d[i][j].second / a[i];
					double new_ans = d[i][j].first + delta;
					double new_sum = d[i][j].second + a[i];
					if (d[i + 1][j].first > new_ans + EPS || (abs(d[i + 1][j].first - new_ans) < EPS && new_sum < d[i + 1][j].second)) {
						d[i + 1][j] = { new_ans, new_sum };
					}
				}
				else {
					double delta = 0;
					double new_ans = d[i][j].first + delta;
					double new_sum = a[i];
					if (d[i + 1][j + 1].first > new_ans + EPS || (abs(d[i + 1][j + 1].first - new_ans) < EPS && new_sum < d[i + 1][j + 1].second)) {
						d[i + 1][j + 1] = { new_ans, new_sum };
					}
				}
			}
		}
	}
	out << fixed << setprecision(16) << d[n][k].first + n << endl;
}
