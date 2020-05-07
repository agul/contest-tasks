#include "Head.h"
#include "IO/IO.h"
#include "Graph/Graph.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111;
const int MAXM = 11111;

int start, finish;
UndirectedGraph graph(MAXN, MAXM, Graph::GT_WEIGHTED);
bool used[MAXN];

bool dfs(int v, int cur_len, int max_len) {
	used[v] = true;
	for (const auto& it : graph.edges[v]) {
		int to = graph.to[it];
		int len = graph.weight[it];
		int new_len = cur_len | len;
		if (used[to] || (new_len | max_len) != max_len) {
			continue;
		}
		if (to == finish) {
			return true;
		}
		if (dfs(to, new_len, max_len)) {
			return true;
		}
	}
	return false;
}

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	graph.clear();
	graph.initGraph(n);
	for (int i = 0; i < m; ++i) {
		int from, to, len;
		io >> from >> to >> len;
		--from, --to;
		graph.addBidirectionalWeightedEdge(from, to, len);
	}
	io >> start >> finish;
	--start, --finish;
	for (int max_len = 1; max_len <= 1024; ++max_len) {
		fill(used, 0);
		if (dfs(start, 0, max_len)) {
			io << max_len << endl;
			return;
		}
	}
	io << -1 << endl;
}
