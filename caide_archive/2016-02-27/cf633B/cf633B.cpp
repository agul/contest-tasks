#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n;
	int cur = 0;
	io >> n;
	for (int i = 5; ; i += 5) {
		int tmp = i;
		while (!(tmp % 5)) {
			++cur;
			tmp /= 5;
		}
		if (cur > n) {
			io << 0 << endl;
			return;
		}
		if (cur == n) {
			io << 5 << endl;
			for (int j = i; j < i + 5; ++j) {
				io << j << " ";
			}
			io << endl;
			return;
		}
	}
}
