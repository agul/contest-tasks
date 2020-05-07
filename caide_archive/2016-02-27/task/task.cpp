#include "Head.h"
#include "IO/IO.h"
#include "SegmentTree.h"
#include "SuffixArray.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 255555;

int lcp[MAXN], p[MAXN];
char s[MAXN];

void solve(istream& ins, ostream& out) {
	int n;
	ins >> n >> s;
	for (int i = 0; i < n; ++i) {
		s[i] -= 'A';
	}
	suffixLCPArrayCyclic(p, lcp, s, n, 26);
	ll ans = 0;
	for (int i = 0; i < n - 1; ++i) {
		ans += lcp[i];
	}
	out << fixed << setprecision(3) << ans / (n - 1.) << endl;
}
