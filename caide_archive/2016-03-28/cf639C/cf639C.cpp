#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 222222;

const ll inf = 1e14;

int n, m, k, pos, fst, ans;
ll a[MAXN], b[MAXN];

inline void process(int i) {
	if (a[i] % 2 != 0) {
		a[i + 1] += (a[i] - 1) / 2;
		a[i] = 1;
	}
	else {
		a[i + 1] += a[i] / 2;
		a[i] = 0;
	}
}

void run2() {
	ll val = 0;
	ans = 0;
	for (int i = n - 1; i >= 0; --i) {
		val = val * 2 + a[i];
		if (i <= fst) {
			ll cur = b[i] - val;
			if (abs(cur) <= k && (cur != 0 || (cur == 0 && i != m - 1))) {
				++ans;
			}
		}
		if (abs(val) > inf) {
			break;
		}
	}
	io << ans << endl;
}

void solve(istream& ins, ostream& out) {
	io >> n >> k;
	++n;
	m = n;
	fill(a, 0);
	for (int i = 0; i < n; ++i) {
		io >> b[i];
		a[i] += b[i];
		process(i);
	}
	if (a[n] != 0) {
		++n;
	}
	while (abs(a[n - 1]) > 1) {
		process(n - 1);
		++n;
	}
	fst = m - 1; 
	for (int i = 0; i < m; ++i) {
		if (a[i] != 0) {
			fst = i;
			break;
		}
	}
	run2();
}
