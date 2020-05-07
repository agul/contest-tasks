#include "Head.h"
#include "IO/IO.h"
#include "Graph/Graph.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 222222;

int n, ans;
UndirectedGraph graph(MAXN, MAXN);
vvi res;

void dfs(int v, int p, int used_day) {
	int cur_day = 0;
	for (const auto& it : graph.edges[v]) {
		if (cur_day == used_day) {
			++cur_day;
		}
		int to = graph.to[it];
		if (to == p) {
			continue;
		}
		res[cur_day].emplace_back(it / 2 + 1);
		dfs(to, v, cur_day);
		++cur_day;
	}
}

void solve(istream& ins, ostream& out) {
	io >> n;
	graph.clear();
	graph.initGraph(n);
	for (int i = 1; i < n; ++i) {
		int from, to;
		io >> from >> to;
		--from, --to;
		graph.addBidirectionalEdge(from, to);
	}
	int root = graph.find_vertex_with_max_degree();
	int ans = graph.edges[root].size();
	res.clear();
	res.resize(ans);
	dfs(root, -1, -1);
	io << ans << endl;
	for (const auto& vec : res) {
		io << vec.size() << ' ';
		for (const auto& it : vec) {
			io << it << ' ';
		}
		io << endl;
	}
}
