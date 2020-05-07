#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

const int ANS[] = { 2,3,5,7,23,37, 53,73,373 };

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	if (n > 9) {
		out << -1 << endl;
		return;
	}
	out << ANS[n - 1] << endl;
}
