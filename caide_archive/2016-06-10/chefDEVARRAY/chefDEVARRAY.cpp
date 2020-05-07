#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	int n;
	in >> n >> __;
	vector<int> a(n);
	in >> a;
	sort(all(a));
	for (int _ = 0; _ < __; ++_) {
		int x;
		in >> x;
		out << (x >= a.front() && x <= a.back() ? "Yes" : "No") << std::endl;
	}
}
