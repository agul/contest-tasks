#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n, m, d;
		in >> n >> m >> d;
		vector<int> a(n);
		in >> a;
		vector<int> pref(n + 1);
		pref[0] = 0;
		for (int i : range(n)) {
			pref[i + 1] = pref[i] + a[i];
		}
		int L = 0, R = 1e9;
		if ((n & 1) != 0 || n < (m - 1) * 2) {
			out << "BAD" << endl;
			continue;
		}
		d *= 2;
		while (R - L > 1) {
			int rest = m - 1;
			int md = (L + R) >> 1;
			int last = 0;
			bool ok = true;
			for (int i = 2; i <= n; i += 2) {
				int mid = (last + i) >> 1;
				if (max(pref[i] - pref[mid], pref[mid] - pref[last]) > md || i - last > d) {
					ok = false;
					break;
				}
				if (i == n || i + 2 - last > d || max(pref[i + 2] - pref[mid + 1], pref[mid + 1] - pref[last]) > md) {
					--rest;
					last = i;
				}
			}
			ok &= (rest >= 0);
			(ok ? R : L) = md;
		}
		if (R == 1000000000) {
			out << "BAD" << endl;
			continue;
		}
		out << R << endl;
	}
}
