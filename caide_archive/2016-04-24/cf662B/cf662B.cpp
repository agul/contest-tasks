#include "Head.h"
#include "IO/IO.h"
#include "Graph/Graph.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

std::vector<std::vector<pii>> graph;
std::vector<int> weights;
bool used[MAXN];

void unmark(int v) {
	for (const auto& it : graph[v]) {
		weights[it.second] ^= 1;
	}
}

void dfs(const int v, const int recolor, const int need, set<int>& cur) {
	used[v] = true;
	bool add = false;
	for (const auto& it : graph[v]) {
		if (weights[it.second] != need) {
			add = true;
		}
	}
	if (add) {
		if (recolor) {
			cur.emplace(v);
		}
		for (const auto& it : graph[v]) {
			int& weight = weights[it.second];
			if (recolor) {
				weight ^= 1;
			}
		}
		for (const auto& it : graph[v]) {
			int& weight = weights[it.second];
			int new_recolor = 0;
			if (weight != need) {
				new_recolor = 1;
			}
			if (!used[it.first]) {
				dfs(it.first, new_recolor, need, cur);
			}
		}
	}
}

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	graph.clear();
	weights.clear();
	graph.resize(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		char ch;
		io >> from >> to >> ch;
		--to, --from;
		int color = (ch == 'B' ? 1 : 0);
		graph[from].emplace_back(to, i);
		graph[to].emplace_back(from, i);
		weights.emplace_back(color);
	}
	int bad = n + 5;
	vector<int> ans(bad, -1);
	int median = n / 2;
	for (int color = 0; color <= 1; ++color) {
		fill_n(used, n, false);
		set<int> cur;
		for (int i = 0; i < n; ++i) {
			if (!used[i]) {
				dfs(i, 1, color, cur);
			}
		}
		int cnt = std::count(all(weights), color ^ 1);
		for (const auto& it : cur) {
			unmark(it);
		}
		if (cnt == 0) {
			std::vector<int> best;
			if (cur.size() > median) {
				for (int i = 0; i < n; ++i) {
					if (cur.count(i) == 0) {
						best.emplace_back(i);
					}
				}
			}
			else {
				best = { cur.begin(), cur.end() };
			}
			if (ans.size() > best.size()) {
				ans.swap(best);
			}
		}
	}
	if (ans.size() == bad) {
		io << -1 << endl;
		return;
	}
	io << ans.size() << endl;
	for (const auto& it : ans) {
		io << it + 1 << " ";
	}
	io << endl;
}
