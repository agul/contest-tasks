#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	ll k;
	in >> n >> k;
	ll cnt = (1LL << n) - 1;
	int step = n;
	while (k >= 1) {
		ll half_cnt = cnt / 2;
		if (k == half_cnt + 1) {
			out << step << endl;
			return;
		}
		if (k > half_cnt) {
			k -= half_cnt + 1;
		}
		cnt /= 2;
		--step;
	}
}
