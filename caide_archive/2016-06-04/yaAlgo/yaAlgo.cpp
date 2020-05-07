#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	int p, a, b;
	in >> p >> a >> b;
	int ans = INF;
	if (b <= p) {
		umin(ans, max(a + b, p));
	}
	out << (ans == INF ? -1 : ans) << endl;
}
