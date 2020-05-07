#include "Head.h"
#include "IO/IO.h"
#include "Stack.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;
const int MAXM = 111;

bool used[MAXN];
vector<int> p;

int dfs(int v) {
	used[v] = true;
	int to = p[v];
	if (used[to]) {
		return 1;
	}
	return 1 + dfs(to);
}

void solve(istream& ins, ostream& out) {
	int big = 0;
	for (int k = 2; k <= 1000; ++k) {
		int n = 5 * k;
		p.resize(n);
		int cur_ind = 0;
		for (int i = 0; i < k; ++i) {
			p[i * 5] = cur_ind++;
			p[i * 5 + 1] = cur_ind++;
		}
		for (int i = 0; i < k; ++i) {
			p[i * 5 + 2] = cur_ind++;
			p[i * 5 + 3] = cur_ind++;
		}
		for (int i = 0; i < k; ++i) {
			p[i * 5 + 4] = cur_ind++;
		}
		int cnt = 0;
		fill(used, 0);
		for (int i = 0; i < n; ++i) {
			if (!used[i]) {
				++cnt;
				int val = dfs(i);
				io << i << ' ' << val << endl;
				// umax(big, val);
			}
		}
		umax(big, cnt);
		io << "###########" << endl;
	}
	io << "BIGGEST: " << big << endl;
}
