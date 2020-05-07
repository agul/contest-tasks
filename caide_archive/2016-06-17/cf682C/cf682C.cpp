#include "base/header.hpp"
#include "graph/graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 1111;

Graph<int, GraphType::Weighted> graph;
vector<ll> a;

int dfs(const int v, ll sum) {
	umax(sum, 0LL);
	if (sum > a[v]) {
		return 0;
	}
	int saved = 1;
	for (const auto& it : graph.edges(v)) {
		saved += dfs(it.to(), sum + it.weight());
	}
	return saved;
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	a.resize(n);
	in >> a;
	graph.clear();
	graph.init(n);
	for (int i : range(1, n)) {
		int p, v;
		in >> p >> v;
		graph.add_directed_edge(p - 1, i, v);
	}
	const int saved = dfs(0, 0);
	out << n - saved << endl;
}
