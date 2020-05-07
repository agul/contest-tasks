#include "Head.h"
#include "IO/IO.h"
#include "Queue.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111;

void rec(ll N, ll R) {
	ll NmodR = 0;
	for (;;) {
		if ((N - NmodR)%(-R) == 0) {
			ll NdivR = -((N - NmodR) / (-R));
			if (NdivR != 0) {
				rec(NdivR, R);
			}
			break;
		}
		NmodR++;
	}
	io << NmodR;
}


void solve(istream& ins, ostream& out) {
	for (;;) {
		char ch;
		io >> ch;
		if (ch == 'e') {
			break;
		}
		if (ch == 't') {
			char x;
			io >> x;
		} else {
			char x;
			io >> x >> x >> x;
		}
		ll N, R;
		io >> R >> N;
		if (ch == 't') {
			if (N == 0) {
				io << 0 << endl;
			}  else {
				rec(N, R);
				io << endl;
			}
		} else {
			ll ans = 0;
			ll t = 1;
			if (N == 0) {
				io << 0 << endl;
				continue;
			}
			while (N != 0) {
				ans += (N % 10) * t;
				N /= 10;
				t *= R;
			}
			io << ans << endl;
		}
	}
}
