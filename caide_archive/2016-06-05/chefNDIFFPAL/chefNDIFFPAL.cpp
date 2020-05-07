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
		std::string s;
		for (int i = 0; i < n; ++i) {
			s += 'a' + (i % 3);
		}
		out << s << endl;
	}
}
