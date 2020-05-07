#include "Head.h"
#include "IO/IO.h"
#include "Matrix.h"
#include "HashMap.h"
#include "DSU.h"
#include "Graph/Graph.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 1111111;

int n, m, compressed[MAXN], wh[MAXN], order[MAXN], vals[MAXN];
DSU dsu(MAXN);
Graph inGraph(MAXN, MAXN * 2), graph(MAXN, MAXN * 2);
oaht::hash_map<pii, bool> edges;

void add_edge(int from, int to) {
	auto& it = edges[{from, to}];
	if (it) {
		return;
	}
	it = true;
	graph.addDirectedEdge(from, to);
}

inline int get_id(int x, int y) {
	return x * m + y;
}

void solve(istream& ins, ostream& out) {
	edges.clear();
	graph.clear();
	inGraph.clear();
	io >> n >> m;
	Matrix<int> a(n, m);
	for (auto& row : a) {
		for (auto& cell : row) {
			io >> cell;
		}
	}
	int vc = n * m;
	inGraph.initGraph(vc);
	dsu.init(vc);
	for (int i = 0; i < n; ++i) {
		vector<pii> row;
		row.reserve(m);
		for (int j = 0; j < m; ++j) {
			row.emplace_back(a[i][j], j);
 		}
		sort(all(row));
		for (int j = 1; j < m; ++j) {
			int cur_vertex = get_id(i, row[j].Y);
			int prev_vertex = get_id(i, row[j - 1].Y);
			if (row[j].X == row[j - 1].X) {
				dsu.unite(prev_vertex, cur_vertex);
			} else {
				inGraph.addDirectedEdge(prev_vertex, cur_vertex);
			}
		}
	}
	for (int j = 0; j < m; ++j) {
		vector<pii> col;
		col.reserve(n);
		for (int i = 0; i < n; ++i) {
			col.emplace_back(a[i][j], i);
		}
		sort(all(col));
		for (int i = 1; i < n; ++i) {
			int cur_vertex = get_id(col[i].Y, j);
			int prev_vertex = get_id(col[i - 1].Y, j);
			if (col[i].X == col[i - 1].X) {
				dsu.unite(prev_vertex, cur_vertex);
			}
			else {
				inGraph.addDirectedEdge(prev_vertex, cur_vertex);
			}
		}
	}
	dsu.finalize();
	fill(compressed, -1);
	int cnt = 0;
	for (int i = 0; i < dsu.size(); ++i) {
		int v = dsu.p[i];
		if (compressed[v] == -1) {
			compressed[v] = cnt++;
		}
	}
	graph.initGraph(cnt);
	for (int i = 0; i < vc; ++i) {
		int cur_vertex = compressed[dsu.p[i]];
		for (const auto& it : inGraph.edges[i]) {
			int to = inGraph.to[it];
			int to_vertex = compressed[dsu.p[to]];
			add_edge(cur_vertex, to_vertex);
		}
	}
	graph.topSortAcyclic(order);
	fill(vals, 0);
	for (int i = 0; i < cnt; ++i) {
		int v = order[i];
		if (vals[v] == 0) {
			vals[v] = 1;
		}
		for (const auto& it : graph.edges[v]) {
			int to = graph.to[it];
			umax(vals[to], vals[v] + 1);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int id = get_id(i, j);
			int cur_set = dsu.p[id];
			int comp = compressed[cur_set];
			int val = vals[comp];
			io << val << ' ';
		}
		io << endl;
	}
}
