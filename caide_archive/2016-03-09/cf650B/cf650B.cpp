#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 555555;

int n;
ll fw[MAXN], bw[MAXN], fwa[MAXN], bwa[MAXN], watch[MAXN];
char s[MAXN];

inline int nxt(int x) {
	return add_mod(x, 1, n);
}

int prv(int x) {
	return sub_mod(x, 1, n);
}

void solve(istream& ins, ostream& out) {
	ll a, b, t;
	io >> n >> a >> b >> t;
	io >> s;
	fill(fw, 0);
	fill(bw, 0);
	for (int i = 0; i < n; ++i) {
		watch[i] = 1 + (s[i] == 'w' ? b : 0);
	}
	fw[0] = bw[0] = fwa[0] = bwa[0] = watch[0];
	for (int i = 1; i < n; ++i) {
		fw[i] = fw[i - 1] + watch[i];
		fwa[i] = fwa[i - 1] + watch[i] + a;
	}
	for (int i = n - 1; i > 0; --i) {
		bw[i] = bw[nxt(i)] + watch[i];
		bwa[i] = bwa[nxt(i)] + watch[i] + a;
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (fwa[i] <= t) {
			umax(ans, i + 1);
		}
	}
	for (int i = n - 1; i > 0; --i) {
		if (bwa[i] <= t) {
			umax(ans, n - i + 1);
		}
	}
	for (int i = n - 1; i > 0; --i) {
		ll cur_value = bw[i] + a * 2 * (n - i) - watch[0];
		if (cur_value > t) {
			break;
		}
		ll rem = t - cur_value;
		int ind = lower_bound(fwa, fwa + i, rem) - fwa;
		if (ind == i) {
			--ind;
		}
		if (ind <= 0) {
			continue;
		}
		if (fwa[ind] > rem) {
			--ind;
		}
		umax(ans, ind + n - i + 1);
	}
	std::reverse(bwa, bwa + n);
	for (int i = 0; i < n; ++i) {
		ll cur_value = fw[i] + a * 2 * i;// -watch[0];
		if (cur_value > t) {
			break;
		}
		ll rem = t - cur_value;
		int ind = lower_bound(bwa, bwa + n - i - 1, rem) - bwa;
		if (ind == n - i - 1) {
			--ind;
		}
		if (ind <= 0) {
			continue;
		}
		if (bwa[ind] > rem) {
			--ind;
		}
		umax(ans, ind + 1 + i + 1);
	}
	io << ans << endl;
}
