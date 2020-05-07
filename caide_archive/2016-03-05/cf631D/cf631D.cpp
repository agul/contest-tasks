#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 2222222;

char s[MAXN];

void parse_string(vector<pli>& a, int n) {
	for (int i = 0; i < n; ++i) {
		int x;
		io >> x;
		char ch;
		io >> ch >> ch;
		if (!a.empty() && a.back().Y == ch) {
			a.back().X += x;
		}
		else {
			a.emplace_back(x, ch);
		}
	}
}

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	vector<pli> a, b;
	parse_string(a, n);
	parse_string(b, m);
	n = a.size();
	m = b.size();
	ll ans = 0;
	if (m > 2) {
		vector<pli> c;
		copy(b.begin() + 1, b.begin() + m - 1, back_inserter(c));
		c.emplace_back(INF, INF);
		copy(all(a), back_inserter(c));
		int len = n + m - 1;
		vector<int> p(len);
		p[0] = 0;
		for (int i = 1; i < len; ++i) {
			int j = p[i - 1];
			while (j > 0 && c[i] != c[j]) {
				j = p[j - 1];
			}
			if (c[i] == c[j]) {
				++j;
			}
			p[i] = j;
		}
		for (int i = m; i < len - 1; ++i) {
			if (p[i] == m - 2 && a[i - m + 1 - m + 2].Y == b[0].Y && a[i - m + 1 - m + 2].X >= b[0].X && a[i - m + 1 + 1].Y == b[m - 1].Y && a[i - m + 1 + 1].X >= b[m - 1].X) {
				++ans;
			}
		}
	} else
	if (m == 2) {
		for (int i = 0; i < n - 1; ++i) {
			if (a[i].Y == b[0].Y && a[i + 1].Y == b[1].Y && a[i].X >= b[0].X && a[i + 1].X >= b[1].X) {
				++ans;
			}
		}
	}
	else {
		for (int i = 0; i < n; ++i) {
			if (a[i].Y == b[0].Y) {
				ans += max(0LL, a[i].X - b[0].X + 1);
			}
		}
	}
	io << ans << endl;
}
