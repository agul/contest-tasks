#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	ll s, x;
	io >> s >> x;
	ll ans = 1;
	int mx = 0;
	for (int i = 0; i < 44; ++i) {
		if (x & (1LL << i)) {
			s -= (1LL << i);
			ans <<= 1;
		}
	}
	if (s < 0 || s & 1) {
		io << 0 << endl;
		return;
	}
	if (s == 0) {
		ans -= 2;
	}
	bool ok = true;
	for (int i = 1; i < 44; ++i) {
		if (s & (1LL << i)) {
			ok &= ((x & (1LL << (i - 1))) == 0);
		}
	}
	io << (ok ? ans : 0) << endl;
}
