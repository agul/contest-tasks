#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	vector<pii> coms;
	for (int i = 0; i < m; ++i) {
		int command;
		int value = 0;
		io >> command;
		if (command == 1) {
			io >> value;
		}
		coms.emplace_back(command, value);
	}
	vector<int> ans(n, 0);
	for (int i = 1; i <= 2; ++i) {
		ll delta = 0;
		for (const auto& it : coms) {
			if (it.X == 1) {
				delta += it.Y;
			}
			else 
			if ((i + delta) % 2 == 0) {
				--delta;
			}
			else {
				++delta;
			}
		}
		for (int j = i; j <= n; j += 2) {
			int cur = ((j + delta) % n + n) % n;
			if (cur == 0) {
				cur = n;
			}
			ans[cur - 1] = j;
		}
	}
	for (const auto& it : ans) {
		io << it << ' ';
	}
	io << endl;
}
