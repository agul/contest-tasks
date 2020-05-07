#include "base/header.hpp"
#include "maths/matrix.hpp"
#include "maths/mod_int.hpp"
#include "maths/maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

inline int pc(ll x) {
	int res = 0;
	while (x > 0) {
		res += (x & 1);
		x >>= 1;
	}
	return res;
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	ll m;
	in >> n >> m;
	vector<ll> a(n);
	in >> a;
	Matrix<ModInt<int>> g(n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (pc(a[i] ^ a[j]) % 3 == 0) {
				g[i][j] = 1;
			}
		}
	}
	auto b = g.binpow(m - 1);
	ModInt<int> ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			ans += b[i][j];
		}
	}
	out << ans << endl;
}
