#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;
ll d[22][132], d2[22][132];

void solve(istream& ins, ostream& out) {
	ll n, k, ans = 0;
	io >> n >> k;
	vector<int> a;
	while (n) {
		a.push_back(n % 10);
		n /= 10;
	}
	int l = a.size();
	vector<int> s(l + 2);
	s[l] = 0;
	for (int i = l - 1; i >= 0; i--)
		s[i] = a[i] + s[i + 1];

	vector<int> ak;
	while (k) {
		ak.push_back(k % 10);
		k /= 10;
	}
	int lk = ak.size();
	vector<int> sk(l + 2);
	sk[lk] = 0;
	for (int i = lk - 1; i >= 0; i--)
		sk[i] = ak[i] + sk[i + 1];

	fill(d, 0);
	fill(d2, 0);
	d[0][0] = 1;
	for (int i = 1; i < 10; i++) {
		d[1][i] = 1;
		d2[1][i] = 1;
	}
	for (int k = 1; k <= l; k++) {
		for (int i = 1; i < 120; i++) {
			for (int tt = 0; tt <= 9; tt++) {
				d[k + 1][i + tt] += d[k][i];
			}
		}
	}
	d[1][0] = 1;

	d2[0][0] = 1;
	d2[1][0] = 1;
	for (int k = 1; k <= l; k++) {
		for (int i = 0; i < 120; i++) {
			for (int tt = 0; tt <= 9; tt++) {
				d2[k + 1][i + tt] += d2[k][i];
			}
		}
	}

	int sum = sk[0];
	for (int p = 1; p < sum; ++p) {
		for (int i = 1; i < l; ++i) {
			ans += d[i][p];
		}
	}


	for (int p = 1; p < sum; ++p) {
		int left = p;
		for (int j = l - 1; j >= 0; --j) {
			for (int k = (j == l - 1 ? 1 : 0); k < min(left + 1, a[j]); ++k) {
				ans += d2[j][left - k];
			}
			left -= a[j];
		}
		if (left == 0) {
			++ans;
		}
	}

	for (int i = 1; i < lk; ++i) {
		ans += d[i][sum];
	}

	for (int p = sum; p <= sum; ++p) {
		int left = p;
		for (int j = lk - 1; j >= 0; --j) {
			for (int k = (j == lk - 1 ? 1 : 0); k < min(left, ak[j]); ++k) {
				ans += d2[j][left - k];
			}
			left -= ak[j];
		}
	}

	io << ans + 1 << endl;
	return;
}
