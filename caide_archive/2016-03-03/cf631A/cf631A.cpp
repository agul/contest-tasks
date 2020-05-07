#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	int cur_a = 0;
	int cur_b = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		io >> x;
		cur_a |= x;
	}
	for (int i = 0; i < n; ++i) {
		int x;
		io >> x;
		cur_b |= x;
	}
	io << (cur_a + cur_b) << endl;
}
