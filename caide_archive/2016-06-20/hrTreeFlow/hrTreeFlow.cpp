#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

UndirectedGraph<ll, GraphType::Weighted> graph;

void calc_dist(const size_t v, const size_t p, const ll len, std::vector<ll>& dist) {
	umax(dist[v], len);
	for (const auto& it : graph.edges(v)) {
		const size_t to = it.to();
		if (to == p) {
			continue;
		}
		calc_dist(to, v, len + it.weight(), dist);
	}
}

pli find_far(const int v, const int p, const ll len) {
	pli ans = { len, v };
	for (const auto& it : graph.edges(v)) {
		int to = it.to();	
		if (to == p) {
			continue;
		}
		umax(ans, find_far(to, v, len + it.weight()));
	}
	return ans;
}

void solve(std::istream& in, std::ostream& out) {
	graph.clear();
	int n;
	in >> n;
	graph.init(n);
	for (int i : range(n - 1)) {
		int from, to;
		ll w;
		in >> from >> to >> w;
		graph.add_bidirectional_edge(from - 1, to - 1, w);
	}
	std::vector<ll> a(n);
	calc_dist(0, -1, 0, a);
	std::vector<ll> b(n);
	calc_dist(n - 1, -1, 0, b);
	ll ans = min(accumulate(all(a), 0), accumulate(all(b), 0));
	out << ans << endl;
}
