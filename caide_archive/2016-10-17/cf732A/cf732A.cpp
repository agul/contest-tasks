#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int k, x;
	in >> k >> x;
	for (int i : range(1, 10)) {
		int sum = k * i;
		if (sum % 10 == 0 || sum % 10 == x) {
			out << i << endl;
			break;
		}
	}
}
