#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1010;

const int SIZE = 1024;
const int ITER = 100;
using Shelf = std::bitset<SIZE>;

Shelf box[MAXN][MAXN];
int vals[MAXN];

enum Type {
	ADD,
	REMOVE,
	FLIP,
	ROLLBACK
};

struct Query {
	Type type;
	int x, y;

	friend istream& operator >>(istream& in, Query& rhs) {
		int type;
		in >> type >> rhs.x;
		rhs.type = type - 1;
		if (type == ADD || type == REMOVE) {
			--rhs.x;
			in >> rhs.y;
			--rhs.y;
		}
		else if (type == FLIP) {
			--rhs.x;
		}
		return in;
	}

};

void solve(std::istream& in, std::ostream& out) {
	int n, m, q;
	in >> n >> m >> q;
	vector<Query> a(q);
	in >> a;
	int ans = 0;
	fill(box, 0);
	fill(vals, 0);
	int cur_index = 1;
	for (int i : inclusiveRange(1, q)) {
		const auto& query = a[i - 1];
		if (query.type == ADD) {
			auto& it = box[query.x][cur_index][query.y];
			if (it == 0) {
				++ans;
				it = 1;
			}
		} 
		else if (query.type == REMOVE) {
			auto& it = box[query.x][cur_index][query.y];
			if (it == 1) {
				--ans;
				it = 0;
			}
		} 
		else if (query.type == FLIP) {
			auto& it = box[query.x][cur_index];
			it.flip();
			int cnt = it.count();
			int rev_cnt = SIZE - cnt;
			if (it[SIZE - 1]) {
				cnt -= SIZE - m;
			}
			else {
				rev_cnt -= SIZE - m;
			}
			ans = ans - rev_cnt + cnt;
		}
		else {
			int pos = query.x;
			int id = pos / ITER;
			ans = vals[id];
			for (int row : range(n)) {
				box[row][cur_index] = box[row][id];
			}
			for (int j : range(id * ITER, pos)) {

			}
		}
		vals[cur_index] = ans;
		out << ans << endl;
		if (i % ITER == 0) {
			++cur_index;
		}
	}
}
