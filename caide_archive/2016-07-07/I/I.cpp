#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

vector<pair<int, int>> a(555555);
int s = 0;

void ans(int l, int r) {
	if (l == r)
		return;
	if (r - l == 1) {
		a[s++] = make_pair(l, r);
		return;
	}
	if ((r - l + 1) & 1) {
		a[s++] = make_pair(l, r - 1);
		ans(l + (r - l) / 2, r);
		a[s++] = make_pair(l, r - 1);
	}
	else {
		a[s++] = make_pair(l, l + 1);
		ans(l + 1, r);
		a[s++] = make_pair(l, l + 1);
	}
}

void solve(std::istream& in, std::ostream& out) {
	int __;
	in >> __;
	for (int _ = 0; _ < __; _++) {
		s = 0;
		int n;
		in >> n;
		vector<int> b(n);
		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			int k;
			in >> k;
			k--;
			b[i] = k;
			v[k] = i;
		}
		for (int i = n - 1; i > 0; i--) {
			if (v[i] < i) {
				ans(v[i], i);
				int k = v[i], p = b[i];
				v[i] = i;
				b[i] = i;
				b[k] = p;
				v[p] = k;
			}
		}
		out << s<<endl;
		for (int i = 0; i < s; i++) {
			out << a[i].first+1 << ' ' << a[i].second+1 << endl;
		}
	}
}
