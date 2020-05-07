#include "Head.h"
#include "IO.h"
#include "Graph/Graph.h"

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 555555;

int parent[MAXN], depth[MAXN], col[MAXN], Tm[MAXN];
UndirectedGraph graph(MAXN, MAXN);
vector<pii> leaves;

void dfs(int v, int p, int lvl, int comp) {
	col[v] = comp;
	depth[v] = lvl;
	parent[v] = p;
	bool any = false;
	for (const auto& it : graph.edges[v]) {
		int to = graph.to[it];
		if (to == p) {
			continue;
		}
		any = true;
		dfs(to, v, lvl + 1, comp);
	}
	if (!any) {
		leaves.emplace_back(lvl, v);
	}
}

void solve(istream& ins, ostream& out) {
	int n;
	io >> n;
	graph.clear();
	graph.initGraph(n);
	for (int i = 1; i < n; ++i) {
		int to, from;
		io >> from >> to;
		--to, --from;
		graph.addBidirectionalEdge(from, to);
	}
	fill(Tm, 0);
	int cnt = 0, ans = 0;
	for (const auto& it : graph.edges[0]) {
		int to = graph.to[it];
		leaves.clear();
		dfs(to, 0, 1, cnt++);
		sort(all(leaves));
		int prv = 0;
		for (const auto& leaf : leaves) {
			Tm[leaf.Y] = max(leaf.X, prv + 1);
			prv = Tm[leaf.Y];
		}
	}
	for (int i = 0; i < n; ++i) {
		umax(ans, Tm[i]);
	}
	io << ans << endl;
}
