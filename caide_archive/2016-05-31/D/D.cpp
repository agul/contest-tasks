#include "Head.h"
#include "Graph/graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 222222;

unordered_map<int, ll> memo;

ll calc(const ll n, const ll r, const ll p) {
	if (n <= 1) {
		return 0;
	}
	const auto it = memo.find(n);
	if (it != memo.end()) {
		return it->second;
	}
	ll x = (n - 1) * p + r;
	for (int i = 2; i <= n; ++i) {
		umin(x, calc((n - 1) / i + 1, r, p) + p * (i - 1) + r);
	}
	return memo[n] = x;
}

void solve(istream& in, ostream& out) {
	ll n, p, r;
	in >> n >> r >> p;
	memo.clear();
	const ll ans = calc(n, r, p);
	out << ans << endl;
}
