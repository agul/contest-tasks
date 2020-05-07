#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int a, b, c;
	in >> a >> b >> c;
	out << max({ a, b, c }) - min({ a, b, c }) << endl;
}
