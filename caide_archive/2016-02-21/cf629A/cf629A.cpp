#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int row[MAXN], col[MAXN];
char s[MAXN];

void solve(istream& ins, ostream& out) {
	fill(row, 0);
	fill(col, 0);
	int n;
	io >> n;
	for (int i = 0; i < n; ++i) {
		io >> s;
		for (int j = 0; j < n; ++j) {
			if (s[j] == 'C') {
				++row[i];
				++col[j];
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += row[i] * (row[i] - 1) / 2;
		ans += col[i] * (col[i] - 1) / 2;
	}
	io << ans << endl;
}
