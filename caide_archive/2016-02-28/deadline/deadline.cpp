#include "Head.h"
#include "IO/IO.h"
#include "HashMap.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111111;

int compressed[MAXN];
oaht::hash_map<int, int> rows;
vector<pii> events[MAXN];
vector<pii> colored[MAXN];
vector<pair<int, pii>> input;

int get_row(const int row) {
	if (rows.count(row)) {
		return rows[row];
	}
	int sz = rows.size;
	compressed[sz] = row;
	rows[row] = sz;
	return sz;
}

void solve(istream& ins, ostream& out) {
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		int m, n, k, p;
		io >> m >> n >> k >> p;
		rows.clear();
		input.clear();
		for (int i = 0; i < p; ++i) {
			int b, e, row;
			io >> b >> e >> row;
			input.emplace_back(row, pii(b, e));
		}
		sort(all(input));
		for (const auto& it : input) {
			int row = get_row(it.X);
			events[row].emplace_back(it.Y.X, 0);
			events[row].emplace_back(it.Y.Y + 1, 1);
		}
		int rows_cnt = rows.size;
		for (int i = 0; i < rows_cnt; ++i) {
			auto& cur_vector = events[i];
			sort(all(cur_vector));
			int balance = 0;
			int events_cnt = cur_vector.size();
			int cur_index = 0;
			for (int j = 0; j < events_cnt; ++j) {
				pii& e = cur_vector[j];
				if (e.Y) {
					--balance;
					if (balance == 0) {
						cur_vector[cur_index++] = e;
					}
				}
				else {
					++balance;
					if (balance == 1) {
						cur_vector[cur_index++] = e;
					}
				}
			}
			cur_vector.resize(cur_index);
		}
		for (int i = 1; i < rows_cnt - 1; ++i) {
			if (compressed[i - 1] != compressed[i] - 1 || compressed[i + 1] != compressed[i] + 1) {
				continue;
			}
			vector<pii> tmp = events[i];
			std::copy(all(events[i - 1]), back_inserter(tmp));
			std::copy(all(events[i + 1]), back_inserter(tmp));
			sort(all(tmp));
			int balance = 0;
			int last = 0;
			for (const auto& it : tmp) {
				if (it.Y) {
					if (balance == 3 && it.X - last >= k) {
						colored[i - 1].emplace_back(last, 0);
						colored[i - 1].emplace_back(it.X - 1, 1);
						colored[i].emplace_back(last, 0);
						colored[i].emplace_back(it.X - 1, 1);
						colored[i + 1].emplace_back(last, 0);
						colored[i + 1].emplace_back(it.X - 1, 1);
					}
					--balance;
				}
				else {
					++balance;
					if (balance == 3) {
						last = it.X;
					}
				}
			}
		}
		ll ans = 0;
		for (int i = 0; i < rows_cnt; ++i) {
			auto& cur_vector = colored[i];
			sort(all(cur_vector));
			int balance = 0;
			int last = 0;
			for (const auto& it : cur_vector) {
				if (it.Y) {
					--balance;
					if (balance == 0) {
						ans += it.X - last + 1;
					}
				}
				else {
					++balance;
					if (balance == 1) {
						last = it.X;
					}
				}
			}
			events[i].clear();
			colored[i].clear();
		}
		io << ans << endl;
	}
}
