#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		int x;
		in >> x;
		out << (x % 6 == 0 ? "Misha" : "Chef") << endl;
	}
}
