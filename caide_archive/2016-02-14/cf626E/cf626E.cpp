#include "Head.h"
#include "IO/IO.h"
#include "Maths.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 222222;

int n;
ll pref[MAXN];
vector<ll> a;

double check(int offset, int idx) {
	double ret = static_cast<double>(pref[idx] - pref[idx - offset - 1] + pref[n] - pref[n - offset]) / (offset * 2 + 1) - a[idx];
	return ret;
}

void solve(istream& ins, ostream& out) {
	io >> n;
	a.resize(n + 1);
	a[0] = 0;
	for (int i = 1; i <= n; ++i) {
		io >> a[i];
	}
	sort(all(a));
	pref[0] = 0;
	for (int i = 1; i <= n; ++i) {
		pref[i] = pref[i - 1] + a[i];
	}
	double total_best = -LINF;
	int ax = 0, ay = 0;
	for (int i = 1; i <= n; ++i) {
		int L = 0, R = min(i - 1, n - i);
		while (R - L > 2) {
			int diff = (R - L) / 3;
			int m1 = L + diff, m2 = R - diff;
			if (check(m1, i) < check(m2, i)) {
				L = m1;
			}
			else {
				R = m2;
			}
		}
		double val = check(L, i);
		int best = L;
		for (int j = L + 1; j <= R; ++j) {
			if (umax(val, check(j, i))) {
				best = j;
			}
		}
		if (umax(total_best, val)) {
			ay = best;
			ax = i;
		}
	}
	io << (ay * 2 + 1) << endl;
	for (int i = ax - ay; i <= ax; ++i) {
		io << a[i] << ' ';
	}
	for (int i = n - ay + 1; i <= n; ++i) {
		io << a[i] << ' ';
	}
	io << endl;
}

