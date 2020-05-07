#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n, k;
	io >> n >> k;
	if (n == 4 || k < n + 1) {
		io << -1 << endl;
		return;
	}
	vector<int> a(4);
	for (int i = 0; i < 4; ++i) {
		io >> a[i];
	}
	vector<int> b;
	for (int i = 1; i <= n; ++i) {
		if (find(all(a), i) == a.cend()) {
			b.emplace_back(i);
		}
	}
	io << a[0] << " " << a[2] << " ";
	for (const auto& it : b) {
		io << it << " ";
	}
	io << a[3] << " " << a[1] << endl;

	io << a[2] << " " << a[0] << " ";
	for (const auto& it : b) {
		io << it << " ";
	}
	io << a[1] << " " << a[3] << endl;
}
