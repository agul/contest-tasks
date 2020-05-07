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
	vector<int> a(n);
	for (auto& it : a) {
		io >> it;
	}
	sort(all(a));
	int L = 0, R = n - 1;
	while (L <= R) {
		io << a[L++] << ' ';
		if (L > R) {
			break;
		}
		io << a[R--] << ' ';
	}
	io << endl;
}
