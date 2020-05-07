#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	vector<int> a(n);
	vector<int> b(n);
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	for (int j = 0; j < n; ++j) {
		io >> b[j];
	}
	int cnt = 0;
	vector<bool> used_a(n, false);
	vector<bool> used_b(n, false);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (used_b[j]) {
				continue;
			}
			if (a[i] == b[j]) {
				used_a[i] = true;
				used_b[j] = true;
				++cnt;
				break;
			}
		}
	}
	if (cnt == n) {
		io << cnt - 1 << endl;
		return;
	}
	io << cnt + 1 << endl;
}
