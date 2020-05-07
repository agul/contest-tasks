#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	unordered_map<int, ll> x, y;
	unordered_map<pii, ll> points;
	for (int i = 0; i < n; ++i) {
		int xx, yy;
		io >> xx >> yy;
		++x[xx];
		++y[yy];
		++points[{xx, yy}];
	}
	ll ans = 0;
	for (const auto& it : x) {
		ans += it.second * (it.second - 1) / 2;
	}
	for (const auto& it : y) {
		ans += it.second * (it.second - 1) / 2;
	}
	for (const auto& it : points) {
		ans -= it.second * (it.second - 1) / 2;
	}
	io << ans << endl;
}
