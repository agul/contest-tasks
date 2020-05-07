#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

vector<pii> a;

void add_edge(int x, int y) {
	a.emplace_back(x, y);
}

void solve(istream& ins, ostream& out) {
	int n, d, h;
	io >> n >> d >> h;
	if (d > 2 * h) {
		io << -1 << endl;
		return;
	}
	if (d == 1) {
		if (n == 2) {
			io << "1 2" << endl;
		}
		else {
			io << -1 << endl;
		}
		return;
	}
	a.clear();
	int cnt = 1;
	for (int i = 2; i <= h + 1; ++i) {
		add_edge(i - 1, i);
		++cnt;
	}
	if (h < d) {
		add_edge(1, h + 2);
		++cnt;
		for (int i = 1; i < d - h; ++i) {
			add_edge(h + 2 + i - 1, h + 2 + i);
			++cnt;
		}
		for (int i = cnt + 1; i <= n; ++i) {
			add_edge(1, i);
		}
	}
	else {
		for (int i = cnt + 1; i <= n; ++i) {
			add_edge(2, i);
		}

	}
	for (const auto& it : a) {
		io << it.X << " " << it.Y << endl;
	}
}
