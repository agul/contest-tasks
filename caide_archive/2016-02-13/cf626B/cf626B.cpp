#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

char s[MAXN];

void solve(istream& ins, ostream& out) {
	int ls;
	io >> ls >> s;
	string yes = "";
	for (char ch : "BGR") {
		for (int i = 0; i < ls; ++i) {
			if (s[i] == ch && count(all(yes), ch) < 2) {
				yes += ch;
			}
		}
	}
	if (count(all(yes), 'B') == yes.length()) {
		io << "B" << endl;
		return;
	}
	if (count(all(yes), 'G') == yes.length()) {
		io << "G" << endl;
		return;
	}
	if (count(all(yes), 'R') == yes.length()) {
		io << "R" << endl;
		return;
	}
	string ans = "";
	if (count(all(yes), 'B') && count(all(yes), 'G')) {
		ans += 'R';
	}
	if (count(all(yes), 'G') && count(all(yes), 'R')) {
		ans += 'B';
	}
	if (count(all(yes), 'B') && count(all(yes), 'R')) {
		ans += 'G';
	}

	if (count(all(yes), 'B') == 2 && count(all(yes), 'R')) {
		ans += 'R';
	}
	if (count(all(yes), 'B') == 2 && count(all(yes), 'G')) {
		ans += 'G';
	}
	if (count(all(yes), 'G') == 2 && count(all(yes), 'R')) {
		ans += 'R';
	}
	if (count(all(yes), 'G') == 2 && count(all(yes), 'B')) {
		ans += 'B';
	}
	if (count(all(yes), 'R') == 2 && count(all(yes), 'B')) {
		ans += 'B';
	}
	if (count(all(yes), 'R') == 2 && count(all(yes), 'G')) {
		ans += 'G';
	}


	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	io << ans.c_str() << endl;
}
