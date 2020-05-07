#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		int n;
		in >> n;
		vector<int> a(n);
		in >> a;
		bool ok = false;
		for (int i = 2; i < a.size(); ++i) {
			ok |= (a[i - 2] == a[i] && a[i - 1] == a[i]);
		}
		out << (ok ? "Yes" : "No") << endl;
	}
}
