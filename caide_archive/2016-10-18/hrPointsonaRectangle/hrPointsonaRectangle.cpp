#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n;
		in >> n;
		vector<pii> a(n);
		in >> a;
		int minx = INF;
		int miny = INF;
		int maxx = -INF;
		int maxy = -INF;
		for (const auto& it : a) {
			umax(maxx, it.first);
			umax(maxy, it.second);
			umin(minx, it.first);
			umin(miny, it.second);
		}
		bool ok = true;
		for (const auto& it : a) {
			ok &= (it.first == maxx || it.first == minx || it.second == maxy || it.second == miny);
		}
		out << (ok ? "YES" : "NO") << endl;
	}
}
