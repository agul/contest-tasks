#include "Head.h"
#include "IO/IO.h"
#include "Maths.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int cnt[256];
char s[MAXN];

void solve(istream& ins, ostream& out) {
	int n;
	ll m, f;
	io >> n >> m >> f;
	vector<ll> a(n);
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	int cur_ind = 0;
	for (int i = 0; i < n;) {
		while (cur_ind < n - 2 && a[cur_ind + 1] < a[cur_ind]) {
			++cur_ind;
		}
		int buy = cur_ind++;
		while (cur_ind < n - 1 && a[cur_ind + 1] > a[cur_ind]) {
			++cur_ind;
		}
		int sell = cur_ind++;
		ll cur_money = m - f;
		ll cur_amount = cur_money / a[buy];
		cur_money += cur_amount * a[sell];
		cur_money -= f;
		if (cur_money > m) {

		}
		i = cur_ind;
	}
}
