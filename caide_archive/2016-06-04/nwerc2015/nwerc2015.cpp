#include "Head.h"
#include "Graph/graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 222222;

int color[MAXN], order[MAXN];
Graph graph(MAXN, MAXN * 3), rev(MAXN, MAXN * 3), tree(MAXN, MAXN * 3);
std::unordered_set<pii> edges;

void add(int x, int y) {
	if (edges.count({ x, y })) {
		return;
	}
	edges.insert({ x, y });
	--x;
	--y;
	graph.addDirectedEdge(x, y);
	rev.addDirectedEdge(y, x);
}

void add_tree(int x, int y) {
	if (edges.count({ x, y })) {
		return;
	}
	edges.insert({ x, y });
	tree.addDirectedEdge(x, y);
}

void solve(istream& in, ostream& out) {
	int n;
	in >> n;
	vector<int> a(n), b(n), c(n);
	in >> a >> b >> c;
	edges.clear();
	graph.clear();
	tree.clear();
	rev.clear();
	graph.initGraph(n);
	rev.initGraph(n);
	for (int i = 1; i < n; ++i) {
		add(a[i - 1], a[i]);
		add(b[i - 1], b[i]);
		add(c[i - 1], c[i]);
	}
	stronglyConnectedComponents(graph, rev, color);
	edges.clear();
	std::vector<int> vcnt(n, 0);
	int max_color = 0;
	for (int vertex = 0; vertex < n; ++vertex) {

		const int cur_col = color[vertex];
		umax(max_color, cur_col + 1);
		++vcnt[cur_col];
	}
	tree.initGraph(max_color);
	for (const auto& vertex : graph.edges) {
		for (const auto& it : vertex) {
			int to = graph.to[it];
			int from = graph.from[it];
			if (color[to] != color[from]) {
				add_tree(color[from], color[to]);
			}
		}
	}
	tree.topSortAcyclic(order);
	vector<ll> cnt(max_color, 0);
	ll ans = 0;
	for (int i = max_color - 1; i >= 0; --i) {
		int v = order[i];
		for (const auto& it : tree.edges[v]) {
			int to = tree.to[it];
			cnt[v] += cnt[to];
		}
		ans += cnt[v] * vcnt[v];
		cnt[v] += vcnt[v];
	}
	out << ans << endl;
}
