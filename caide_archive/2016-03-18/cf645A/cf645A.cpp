#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

char s[4];

string get() {
	io >> s;
	string ret(s);
	io >> s;
	reverse(s, s + 2);
	ret += string(s);
	string result = "";
	for (auto& ch : ret) {
		if (ch != 'X') {
			result += ch;
		}
	}
	return result;
}

void solve(istream& ins, ostream& out) {
	string a = get(), b = get();
	a += a;
	for (int i = 0; i < 3; ++i) {
		if (a.substr(i, 3) == b) {
			io << "YES" << endl;
			return;
		}
	}
	io << "NO" << endl;
}
