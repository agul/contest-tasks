#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int n, p[MAXN];

inline int prv(int x) {
	return sub_mod(x, 1, n);
}

void solve(istream& ins, ostream& out) {
	io >> n;
	if (n == 1) {
		io << 0 << endl;
		return;
	}
	vector<int> a(n);
	for (auto& it : a) {
		io >> it;
	}
	std::copy(a.begin(), a.end(), std::back_inserter(a));
	
	int start = 0;
	while (a[prv(start)] != 0 && start > 1) {
		start = prv(start);
	}

	io << n - len - 1 << endl;
}
