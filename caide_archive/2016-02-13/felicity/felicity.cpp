#include "Head.h"
#include "IO.h"

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		int n, m;
		io >> n >> m;
		bool ok = false;
		for (int i = 0; i < m; ++i) {
			int from;
			int to;
			io >> from >> to;
			ok |= (from == 1 && to == n);
		}
		io << (ok ? "Jorah Mormont" : "Khal Drogo") << endl;
	}
}
