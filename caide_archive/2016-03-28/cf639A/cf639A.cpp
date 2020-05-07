#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 222222;

int a[MAXN];

struct cmp {
	bool operator() (const int& x, const int& y) const {
		return a[x] > a[y];
	}
};

void solve(istream& ins, ostream& out) {
	int n, k, q;
	io >> n >> k >> q;
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	set<int, cmp> online;
	for (int i = 0; i < q; ++i) {
		int type, id;
		io >> type >> id;
		--id;
		if (type == 1) {
			online.insert(id);
			if (online.size() > k) {
				online.erase(*online.rbegin());
			}
		}
		else {
			io << (online.count(id) > 0 ? "YES" : "NO") << endl;
		}
	}
}
