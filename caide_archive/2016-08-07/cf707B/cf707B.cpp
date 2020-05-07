#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, m, k;
	in >> n >> m >> k;
	UndirectedGraph<int, GraphType::Weighted> graph(n);
	for (int i : range(m)) {
		int x, y, z;
		in >> x >> y >> z;
		--x, --y;
		graph.add_bidirectional_edge(x, y, z);
	}
	int ans = INF;
	vector<int> w(k);
	in >> w;
	vector<bool> used(n, false);
	for (auto& it : w) {
		--it;
		used[it] = true;
	}
	for (const auto& it : w) {
		for (const auto& to : graph.edges(it)) {
			if (used[to.to()]) {
				continue;
			}
			umin(ans, to.weight());
		}
	}
	out << (ans == INF ? -1 : ans) << endl;
}
