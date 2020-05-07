#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	io.assign_files_input_txt();
	io >> __;
	for (int test = 1; test <= __; ++test) {
		if (test % 10 == 0 || test == __) {
			cerr << test << endl;
		}
		io << "Case #" << test << ": ";
		int n;
		io >> n;
		if (n == 0) {
			io << "INSOMNIA" << endl;
			continue;
		}
		ll ans = -1;
		ll cur = n;
		int mask = 0;
		for (int i = 0; i < 1000000; ++i) {
			ll tmp = cur;
			while (tmp > 0) {
				mask |= (1 << (tmp % 10));
				tmp /= 10;
			}
			if (mask == 1023) {
				ans = cur;
				break;
			}
			cur += n;
		}
		io << ans << endl;
	}
}
