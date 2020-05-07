#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int ls;
char s[MAXN];

inline bool nxt(int pos, const char * t) {
	int cur = 0;
	while (pos < ls && t[cur] != 0) {
		if (s[pos] != t[cur]) {
			return false;
		}
		++pos, ++cur;
	}
	return (t[cur] == 0);
}

void solve(istream& ins, ostream& out) {
	next_line(s);
	ls = strlen(s);
	int ans = INF;
	for (int i = 0; i < ls; ++i) {
		if (s[i] == '&') {
			int cnt = 0;
			int x = i + 1;
			while (nxt(x, "amp;")) {
				x += 4;
				++cnt;
			}
			if (nxt(x, "lt;") || nxt(x, "gt;")) {
				++cnt;
				x += 3;
			}
			if (nxt(x, "quot;") || nxt(x, "apos;")) {
				++cnt;
				x += 5;
			}
			i = x - 1;
			umin(ans, cnt);
		} else
		if (s[i] == '"' || s[i] == '>' || s[i] == '<' || s[i] == '\'') {
			ans = 0;
		}
	}
	io << (ans == INF ? -1 : ans) << endl;
}
