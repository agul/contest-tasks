#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	UndirectedGraph<ll, GraphType::Weighted> graph;
	graph.init(n);
	for (int i : range(m)) {
		int from, to;
		ll weight;
		in >> from >> to >> weight;
		graph.add_directed_edge(from, to, weight);
	}
	if (!graph.is_connected()) {
		out << "NON-CONNECTED" << endl;
		return;
	}
	std::vector<size_t> mst;
	const ll ans = graph.minimal_spanning_tree(&mst);
	out << ans << endl;
	std::vector<std::vector<pii>> res(n);
	for (const auto& it : mst) {
		res[graph.from(it)].emplace_back(graph.to(it), graph.weight(it));
		res[graph.to(it)].emplace_back(graph.from(it), graph.weight(it));
	}
	for (const size_t v : graph.vertices()) {
		out << v << " :";
		bool first = true;
		sort(res[v]);
		for (const auto& jt : res[v]) {
			if (first) {
				first = false;
			}
			else {
				out << ",";
			}
			out << " " << jt.first << "(" << jt.second << ")";
		}
		out << endl;
	}
}
