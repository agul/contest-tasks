#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111111;

void solve(istream& ins, ostream& out) {
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		int n, m;
		io >> n >> m;
		vector<vector<int>> a(n, vector<int>(m));
		unordered_map<int, int> compress;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				int x;
				io >> x;
				if (compress.count(x)) {
					x = compress[x];
				}
				else {
					int val = compress.size();
					compress[x] = val;
					x = val;
				}
				a[i][j] = x;
			}
		}
		vector<int> cnt_row(compress.size(), 0);
		for (int i = 0; i < n; ++i) {
			vector<int> row = a[i];
			sort(row.begin(), row.end());
			for (int j = 0; j < m; ) {
				int cur_ind = j;
				while (cur_ind < m && row[cur_ind] == row[j]) {
					++cur_ind;
				}
				umax(cnt_row[row[j]], cur_ind - j);
				j = cur_ind;
			}
		}
		int ans = 0;
		for (int j = 0; j < m; ++j) {
			vector<int> col(n);
			for (int i = 0; i < n; ++i) {
				col[i] = a[i][j];
			}
			sort(col.begin(), col.end());
			for (int i = 0; i < n; ) {
				int cur_ind = i;
				while (cur_ind < n && col[cur_ind] == col[i]) {
					++cur_ind;
				}
				umax(ans, cnt_row[col[i]] + cur_ind - i - 1);
				i = cur_ind;
			}
		}
		io << ans << endl;
	}
}

