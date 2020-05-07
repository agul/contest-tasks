#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 222222;

ll q[MAXN];

void solve(istream& ins, ostream& out) {
	int n, b;
	io >> n >> b;
	int h = 0, t = 0;
	ll last = 0;
	for (int i = 0; i < n; ++i) {
		ll start, len;
		io >> start >> len;
		while (h < t && q[h] <= start) {
			++h;
		}
		if (t - h > b) {
			io << "-1 ";
			continue;
		}
		q[t] = max(last, start) + len;
		last = q[t];
		io << last << ' ';
		++t;
	}
	io << endl;
}
