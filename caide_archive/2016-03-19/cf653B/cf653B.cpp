#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 88;

int ans, n;
char s[MAXN], q[MAXN][4], t[MAXN];

void compress(int pos) {
	if (pos == n - 1) {
		if (t[pos] == 'a') {
			++ans;
		}
		return;
	}
	for (int i = 0; i < __; ++i) {
		if (q[i][0] == t[pos] && q[i][1] == t[pos + 1]) {
			t[pos + 1] = q[i][2];
			compress(pos + 1);
			return;
		}
	}
}

void gen(int pos) {
	if (pos == n) {
		for (int i = 0; i < n; ++i) {
			t[i] = s[i];
		}
		compress(0);
		return;
	}
	for (char ch = 'a'; ch <= 'f'; ++ch) {
		s[pos] = ch;
		gen(pos + 1);
	}
}

void solve(istream& ins, ostream& out) {
	io >> n >> __;
	for (int i = 0; i < __; ++i) {
		char ch;
		io >> q[i] >> ch;
		q[i][2] = ch;
	}
	ans = 0;
	gen(0);
	io << ans << endl;
}
