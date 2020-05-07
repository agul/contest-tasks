#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

UndirectedGraph<int> graph;
vector<int> dist;

pii find_far(const int v, const int p) {
	pii cur = { 0, v };
	for (const auto& it : graph.edges(v)) {
		int to = it.to();
		if (to == p) {
			continue;
		}
		const auto tmp = find_far(to, v);
		umax(cur, tmp);
	}
	++cur.first;
	return cur;
}

void calc_dist(const int v, const int p, const int len) {
	dist[v] = len;
	for (const auto& it : graph.edges(v)) {
		int to = it.to();
		if (to == p) {
			continue;
		}
		calc_dist(to, v, len + 1);
	}
}

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n;
		in >> n;
		graph.clear();
		graph.init(n);
		for (int i : range(n - 1)) {
			int from, to;
			in >> from >> to;
			graph.add_bidirectional_edge(from - 1, to - 1);
		}
		{
			int biggest = graph.find_vertex_with_max_degree();
			if (graph.edges(biggest).size() > 3) {
				out << -1 << endl;
				continue;
			}
		}
		const auto far = find_far(0, -1);
		const int cur_root = far.second;
		dist.assign(n, 0);
		calc_dist(cur_root, -1, 0);
		const int h = *max_element(dist);
		std::vector<size_t> ver;
		for (const size_t v : graph.vertices()) {
			if (graph.edges(v).size() < 3) {
				ver.emplace_back(v);
			}
		}

	}
}
