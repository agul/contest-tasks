#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111;

int n;
char s[MAXN];

void solve(istream& ins, ostream& out) {
	io >> n;
	for (int i = 0; i < n; ++i) {
		io >> s;
		int cur = atoi(s + 4);
		string val(s + 4);
		if (val.length() == 1) {
			if (cur == 9) {
				io << 1989 << endl;
			}
			else {
				io << 1990 + cur << endl;
			}
			continue;
		}
		if (val.length() == 2) {
			if (cur == 99) {
				io << 1999 << endl;
			}
			else {
				io << 2000 + cur << endl;
			}
			continue;
		}
		if (val.length() == 3 && cur < 100) {
			if (cur == 99) {
				io << 2099 << endl;
			}
			else {
				io << 3000 + cur << endl;
			}
			continue;
		}
		if (val.length() == 3 && cur >= 100) {
			io << 2000 + cur << endl;
			continue;
		}
		std::string bad = "3098";
		for (int len = 4; len <= 9; ++len) {
			if (val.length() == len && cur <= stoi(bad)) {
				io << 1 << val.data() << endl;
				break;
			}
			if (val.length() == len) {
				io << val.data() << endl;
				break;
			}
			bad = "1" + bad;
		}
	}
}
