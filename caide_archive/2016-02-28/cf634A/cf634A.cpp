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
	vector<int> a, b;

	for (int i = 0; i < n; ++i) {
		int x;
		io >> x;
		if (x > 0) {
			a.emplace_back(x);
		}
	}
	for (int i = 0; i < n; ++i) {
		int x;
		io >> x;
		if (x > 0) {
			b.emplace_back(x);
		}
	}
	int cur_ind = 0;
	while (a[cur_ind] != b[0]) {
		++cur_ind;
	}
	bool ok = true;
	for (int i = 0; i < a.size(); ++i, add_mod(cur_ind, 1, (int)a.size())) {
		ok &= (a[cur_ind] == b[i]);
	}
	io << (ok ? "YES" : "NO") << endl;
	
}
