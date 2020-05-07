#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111 * 3;

char s[MAXN];

void solve(istream& ins, ostream& out) {
	io >> s;
	int ls = strlen(s);
	ll ans = 0;
	for (int i = 0; i < ls - 1; ++i) {
		int cur = dig(s[i]) * 10 + dig(s[i + 1]);
		cur &= 3;
		if (!cur) {
			ans += i + 1;
		}
	}
	for (int i = 0; i < ls; ++i) {
		ans += !(dig(s[i]) & 3);
	}
	io << ans << endl;
}
