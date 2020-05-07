#include "Head.h"
#include "IO/IO.h"
#include "Graph/Graph.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int dist[4][4], new_dist[4][4];

Graph graph(4, 6, Graph::GT_WEIGHTED);

void add_edge(int from, int to) {
	int w;
	io >> w;
	graph.addDirectedWeightedEdge(from, to, w);
}

void floyd(int d[4][4]) {
	for (int k = 0; k < 4; ++k) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				umin(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
}

void solve(istream& ins, ostream& out) {
	graph.clear();
	graph.initGraph(4);
	add_edge(3, 0);
	add_edge(0, 1);
	add_edge(1, 2);
	add_edge(2, 3);
	add_edge(0, 2);
	add_edge(1, 3);
	int ans = INF;
	for (int edge = 0; edge < 6; ++edge) {
		for (int delta = 0; delta < 200; ++delta) {
			graph.weight[edge] += delta;
			fill(dist, INF);
			for (int i = 0; i < 4; ++i) {
				dist[i][i] = 0;
			}
			for (int i = 0; i < 6; ++i) {
				int from = graph.from[i];
				int to = graph.to[i];
				int w = graph.weight[i];
				dist[from][to] = w;
			}
			floyd(dist);
			memcpy(new_dist, dist, sizeof(dist));
			floyd(new_dist);
			bool ok = true;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					ok &= (dist[i][j] == new_dist[i][j]);
				}
			}
			if (ok) {
				umin(ans, delta);
			}
			graph.weight[edge] -= delta;

		}
	}
	io << (ans == INF ? -1 : ans) << endl;
}
