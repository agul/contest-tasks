#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

bool go(const ll h, const ll w, const std::vector<ll>& vals, const int pos) {
	if (pos == 2) {
		return h * w == vals.back();
	}
	if (h * w < vals[pos]) {
		return false;
	}
	ll L = 1, R = w + 1;
	while (R - L > 1) {
		ll md = (L + R) >> 1;
		if (h * md > vals[pos]) {
			R = md;
		}
		else {
			L = md;
		}
	}
	bool ok = false;
	if (h * L == vals[pos]) {
		ok |= go(h, w - L, vals, pos + 1);
	}
	L = 1, R = h + 1;
	while (R - L > 1) {
		ll md = (L + R) >> 1;
		if (w * md > vals[pos]) {
			R = md;
		}
		else {
			L = md;
		}
	}
	if (w * L == vals[pos]) {
		ok |= go(h - L, w, vals, pos + 1);
	}
	return ok;
}

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		ll h, w;
		vector<ll> vals(3);
		in >> h >> w >> vals;
		bool ok = false;
		sort(vals);
		do {
			ok |= go(h, w, vals, 0);
		} while (next_permutation(vals));
		out << (ok ? "Yes" : "No") << endl;
	}
}
