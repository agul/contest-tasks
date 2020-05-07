#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, a, b;
	string s;
	in >> n >> a >> b >> s;
	out << (s[a - 1] == s[b - 1] ? 0 : 1) << endl;
}
