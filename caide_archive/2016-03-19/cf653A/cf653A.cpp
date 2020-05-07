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
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			for (int k = j + 1; k < n; ++k) {
				if (abs(a[i] - a[j]) < 3 && abs(a[i] - a[k]) < 3 && abs(a[j] - a[k]) < 3 && a[i] != a[j] && a[i] != a[k] && a[j] != a[k]) {
					io << "YES" << endl;
					return;
				}
			}
		}
	}
	io << "NO" << endl;
}
