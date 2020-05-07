#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	if (n == 1) {
		out << -1 << endl;
		return;
	}
	out << n << " " << n + 1 << " " << n * (n + 1) << endl;
}
