#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

char s[MAXN];

void solve(istream& ins, ostream& out) {
	int ls, k;
	io >> ls >> k >> s;
	for (int i = 0; i < ls; ++i) {
		int max_diff = 0;
		int cur_char = 0;
		if (umax(max_diff, 'z' - s[i])) {
			cur_char = 'z';
		}
		if (umax(max_diff, s[i] - 'a')) {
			cur_char = 'a';
		}
		if (k < max_diff) {
			if (s[i] + k > 'z') {
				s[i] -= k;
			}
			else {
				s[i] += k;
			}
			k = 0;
			break;
		}
		k -= max_diff;
		s[i] = cur_char;
	}
	if (k == 0) {
		io << s << endl;
	}
	else {
		io << "-1" << endl;
	}
}
