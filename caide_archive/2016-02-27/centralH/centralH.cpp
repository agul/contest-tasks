#include "Head.h"
#include "IO/IO.h"
#include "Graph/Graph.h"
#include "DSU.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 2002;

using Edge = pair<int, pii>;

int cnt;
Edge e[MAXN * MAXN / 2];
UndirectedGraph graph(MAXN, MAXN);

void dfs(int v, int fs, int len, int p) {
	if (fs < v) {
		e[cnt++] = { len, pii(fs, v) };
	}
	for (const auto& it : graph.edges[v]) {
		int to = graph.to[it];
		if (to == p) {
			continue;
		}
		dfs(to, fs, len + 1, v);
	}
}

void solve(istream& ins, ostream& out) {
	graph.clear();
	int n;
	io >> n;
	graph.initGraph(n);
	for (int i = 1; i < n; ++i) {
		int from, to;
		io >> from >> to;
		--from, --to;
		graph.addBidirectionalEdge(from, to);
	}
	cnt = 0;
	for (int i = 0; i < n; ++i) {
		dfs(i, i, 0, -1);
	}
	graph.clear();
	DSU dsu(n);
	dsu.init(n);
	sort(e, e + cnt, greater<Edge>());
	int ans = 0;
	for (int i = 0; i < cnt; ++i) {
		Edge& edge = e[i];
		if (dsu.unite(edge.Y.X, edge.Y.Y)) {
			ans += edge.X;
		}
	}
	io << ans << endl;
}
