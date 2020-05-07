#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111111;

namespace std {

	template<typename T>
	struct hash<std::pair<T, T>> {
		std::size_t operator()(const std::pair<T, T>& lhs) const {
			return lhs.first * 877117 + lhs.second;
		}
	};

}

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
		vector<pii> cnt_row(compress.size(), { 0,0 });
		unordered_map<pii, int> rows;
		unordered_map<pii, int> cols;
		for (int i = 0; i < n; ++i) {
			vector<int> row = a[i];
			sort(row.begin(), row.end());
			for (int j = 0; j < m; ) {
				int cur_ind = j;
				int cur_color = row[j];
				while (cur_ind < m && row[cur_ind] == cur_color) {
					++cur_ind;
				}
				auto& val = cnt_row[cur_color];
				int cur_val = cur_ind - j;
				rows[{i, cur_color}] = cur_val;
				if (umax(val.X, cur_val)) {
					val.Y = 0;
				}
				if (val.X == cur_val) {
					++val.Y;
				}
				j = cur_ind;
			}
		}
		int ans = 0;
		int candidates_count = 0;
		for (int j = 0; j < m; ++j) {
			vector<int> col(n);
			for (int i = 0; i < n; ++i) {
				col[i] = a[i][j];
			}
			sort(col.begin(), col.end());
			for (int i = 0; i < n; ) {
				int cur_ind = i;
				int cur_col = col[i];
				while (cur_ind < n && col[cur_ind] == cur_col) {
					++cur_ind;
				}
				auto& max_row = cnt_row[cur_col];
				int cur_val = cur_ind - i;
				int cur_cnt = max_row.X + cur_val;
				cols[{j, cur_col}] = cur_ind - i;
				if (umax(ans, cur_cnt)) {
					candidates_count = 0;
				}
				if (ans == cur_cnt) {
					candidates_count += max_row.Y;
				}
				i = cur_ind;
			}
		}
		int intersection_count = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				int cur_val = rows[{i, a[i][j]}] + cols[{j, a[i][j]}];
				if (cur_val == ans) {
					++intersection_count;
				}
			}
		}
		if (intersection_count == candidates_count) {
			--ans;
		}
		io << ans << endl;
	}
}
