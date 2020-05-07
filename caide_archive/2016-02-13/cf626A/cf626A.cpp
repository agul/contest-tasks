#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

const char * DIR = "LDRU";

int t[MAXN], cnt[4][MAXN],cur[4];
char s[MAXN];

inline pii calc_diff() {
	return{ cur[2] - cur[0], cur[3] - cur[1] };
}

void solve(istream& ins, ostream& out) {
	int ls;
	io >> ls >> s;
	for (int i = 0; i < ls; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (s[i] == DIR[j]) {
				t[i + 1] = j;
				break;
			}
		}
	}
	fill(cnt, 0);
	for (int i = 1; i <= ls; ++i) {
		for (int j = 0; j < 4; ++j) {
			cnt[j][i] = cnt[j][i - 1];
		}
		++cnt[t[i]][i];
	}
	int n = ls;
	for (int i = 0; i < 4; ++i) {
		cur[i] = cnt[i][n];
	}
	int ans = 0;
	pii diff = { 0, 0 };
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			for (int k = 0; k < 4; ++k) {
				cur[k] = cnt[k][j] - cnt[k][i - 1];
			}
			if (calc_diff() == diff) {
				++ans;
			}
		}
	}
	io << ans << endl;
}
