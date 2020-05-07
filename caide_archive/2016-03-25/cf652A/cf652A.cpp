#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int h1, h2, a, b;
	io >> h1 >> h2 >> a >> b;
	int diff = h2 - h1;
	int hours = (diff + a - 1) / a;
	if (hours <= 8) {
		io << 0 << endl;
		return;
	}
	if (a <= b) {
		io << -1 << endl;
		return;
	}
	int ans = 1;
	diff -= 8 * a - 12 * b;
	int diff_meters = a - b;
	hours = (max(0, diff - 12 * a) + diff_meters - 1) / diff_meters;
	io << (hours + 11) / 12 + 1 << endl;
}
