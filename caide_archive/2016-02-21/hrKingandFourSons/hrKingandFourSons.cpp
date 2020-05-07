#include "Head.h"
#include "IO/IO.h"
#include "Maths.h"
#include "Matrix.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111;
const int MAXM = 11111;
const int MAXK = 111;

int dp[MAXM][MAXK];

inline Matrix<ll> ppow(Matrix<ll> a, int b) {
	Matrix<ll> ret = Matrix<ll>::identity_matrix(a.rows_cnt(), a.cols_cnt());
	while (b) {
		if (b & 1) {
			ret = ret * a;
		}
		a = a * a;
		b >>= 1;
	}
	return ret;
}

int get_cnt(int x) {
	Matrix<ll> mt(4, 4);
	mt[0] = { 1, 1, 0, 0 };
	mt[1] = { 0, 1, 1, 0 };
	mt[2] = { 0, 0, 1, 1 };
	mt[3] = { 1,0,0,1 };
	return ppow(mt, x)[0][0];
}

void solve(istream& ins, ostream& out) {
	int n, k;
	io >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	fill(dp, 0);
	dp[0][0] = 1;
	for (int i = 0; i < n; ++i) {
		int cnt = get_cnt(a[i]);
		for (int j = 0; j <= k; ++j) {
			ll cur = dp[i][j];
			add_mod(dp[i + 1][j], static_cast<int>(cur));
			mul_mod(cur, (ll)cnt);
			add_mod(dp[i + 1][j + 1], (int)cur);
		}
	}
	io << dp[n][k] << endl;
}
