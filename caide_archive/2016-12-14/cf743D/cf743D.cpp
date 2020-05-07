#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

vector<ll> vals;
UndirectedGraph<int> graph;
ll ans;

pll calc_sums(int v, int p) {
	ll sum = 0;
	vector<ll> children;
	ll mx = -LINF;
	for (const auto& it : graph.edges(v)) {
		const int to = it.to();
		if (to == p) {
			continue;
		}
		const auto cur = calc_sums(to, v);
		sum += cur.first;
		children.emplace_back(cur.second);
		umax(mx, cur.second);
	}
	if (children.size() >= 2) {
		multiset<ll> sums;
		for (const auto& it : children) {
			sums.emplace(it);
		}
		for (const auto& it : children) {
			sums.erase(sums.find(it));
			umax(ans, it + *sums.rbegin());
			sums.emplace(it);
		}
	}
	sum += vals[v];
	return{ sum, std::max(sum, mx) };
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vals.assign(n, 0);
	in >> vals;
	graph = UndirectedGraph<int>(n);
	for (int i : range(n - 1)) {
		int from, to;
		in >> from >> to;
		graph.add_bidirectional_edge(from - 1, to - 1);
	}
	ans = -LINF;
	calc_sums(0, -1);
	if (ans == -LINF) {
		out << "Impossible" << endl;
		return;
	}
	out << ans << endl;
}
