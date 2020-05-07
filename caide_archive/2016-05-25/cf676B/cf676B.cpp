#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n, t;
	io >> n >> t;
	vector<vector<double>> cups(n + 1);
	for (int i = 0; i <= n; ++i) {
		cups[i] = std::vector<double>(i + 1, 0);
	}
	cups[0][0] = t;
	int ans = 0;
	for (int row = 0; row < n; ++row) {
		for (int cup = 0; cup < cups[row].size(); ++cup) {
			double& value = cups[row][cup];
			
			if (value > 1) {
				const double rem = (value - 1) * 0.5;
				cups[row + 1][cup] += rem;
				cups[row + 1][cup + 1] += rem;
				value = 1;
			}

			if (abs(value - 1) < EPS) {
				++ans;
			}
		}
	}
	io << ans << endl;
}
