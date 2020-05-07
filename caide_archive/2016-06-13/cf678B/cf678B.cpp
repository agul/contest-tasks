#include "maths.hpp"
#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	bool leap = is_leap_year(n);
	int cnt = 0;
	while (cnt == 0 || cnt % 7 != 0 || leap != is_leap_year(n)) {
		cnt += 365 + (is_leap_year(n) ? 1 : 0);
		++n;
	}
	out << n << endl;
}
