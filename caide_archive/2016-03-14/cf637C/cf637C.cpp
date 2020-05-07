#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n;
	ins >> n;
	vector<string> a(n);
	for (auto& it : a) {
		ins >> it;
	}
	int mx = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			int cur = 0;
			for (int k = 0; k < 6; ++k) {
				cur += (a[i][k] == a[j][k] ? 1 : 0);
			}
			umax(mx, cur);
		}
	}
	if (n == 1) {
		out << 6 << endl;
		return;
	}
	if (mx >= 4) {
		out << 0 << endl;
		return;
	}
	if (mx >= 2) {
		out << 1 << endl;
		return;
	}
	out << 2 << endl;
}
