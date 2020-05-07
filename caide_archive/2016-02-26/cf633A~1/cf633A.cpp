#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int a, b, c;
	io >> a >> b >> c;
	for (int i = 0; i <= 10000; ++i) {
		if (c == (i * a + (c - a * i) / b * b)) {
			io << "Yes" << endl;
			return;
		}
	}
	io << "No" << endl;
}
