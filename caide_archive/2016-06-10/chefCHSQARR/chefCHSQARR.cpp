#include "Head.h"
#include "sparse_table.hpp"
#include "queue.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111;

using Row = std::vector<int>;
using Field = std::vector<Row>;

void solve(istream& in, ostream& out) {
	int n, m;
	in >> n >> m;
	Field a(n, Row(m));
	Field pref(n + 1, Row(m + 1));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			in >> a[i][j];
			pref[i + 1][j + 1] = pref[i + 1][j] + pref[i][j + 1] + a[i][j] - pref[i][j];
		}
	}
	std::vector<SparseTableCmp<int>> rows(n, SparseTableCmp<int>(m, std::greater<int>()));
	for (int i = 0; i < n; ++i) {
		rows[i].build(a[i]);
	}
	std::vector<CmpQueue<int>> vals(m, CmpQueue<int>(n, std::greater<int>()));
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		int x, y;
		in >> x >> y;
		const size_t rec_size = x * y;
		int ans = INF;

		for (int i = 0; i < n; ++i) {
			for (int j = y - 1; j < m; ++j) {
				if (i == 0) {
					vals[j].clear();
				}
				const int index = rows[i].query(j - y + 1, j + 1);
				vals[j].push(a[i][index]);
				if (i < x - 1) {
					continue;
				}
				const int best = vals[j].min_value();
				const int cur_need = rec_size * best;
				const int cur_sum = pref[i + 1][j + 1] - pref[i + 1 - x][j + 1] - pref[i + 1][j + 1 - y] + pref[i + 1 - x][j + 1 - y];
				umin(ans, cur_need - cur_sum);
				vals[j].pop();
			}
		}
		out << ans << endl;
	}
}
