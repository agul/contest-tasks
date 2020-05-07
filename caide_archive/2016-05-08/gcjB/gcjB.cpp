#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& ins, ostream& out) {
	io.assign_files_input_txt();
	io >> __;
	for (int _ = 1; _ <= __; ++_) {
		cerr << _ << endl;
		io << "Case #" << _ << ": ";
		int n;
		ll m;
		io >> n >> m;
		const ll MAX_CONNECTIONS = (1LL << (n - 2));
		if (m > MAX_CONNECTIONS) {
			io << "IMPOSSIBLE" << endl;
			continue;
		}
		vector<vector<int>> a(n, vector<int>(n, 0));
		if (m == MAX_CONNECTIONS) {
			a[0][n - 1] = 1;
			--m;
		}
		for (int i = 1; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				a[i][j] = 1;
			}
		}
		for (int i = 0; i < n; ++i) {
			if ((1LL << i) & m) {
				a[0][n - 2 - i] = 1;
			}
		}
		io << "POSSIBLE" << endl;
		for (const auto& row : a) {
			for (const auto& col : row) {
				io << col;
			}
			io << endl;
		}
	}
}
