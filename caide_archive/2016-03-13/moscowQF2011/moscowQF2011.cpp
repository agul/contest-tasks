#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 2222222;

ll tmpx, tmpy;

ll calc(ll money, ll fee, ll buy, ll sell, ll& buy_day, ll& sell_day) {
	if (money < fee) {
		return money;
	}
	ll amount = (money - fee) / buy;
	ll res = amount * sell - fee + (money - fee) % buy;
	if (res > money) {
		buy_day = amount;
		sell_day = -amount;
		return res;
	}
	return money;
}

void solve(istream& ins, ostream& out) {
	freopen("output.txt", "w", stdout);
	cout << "200000" << endl;
	for (int i = 0; i < 200000; ++i) {
		cout << "0 0" << endl;
	}
}
