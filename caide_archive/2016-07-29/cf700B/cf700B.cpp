#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

int total;
UndirectedGraph<int> graph;
vector<int> cnt;
vector<ll> dp;
vector<bool> university;

void dfs(const int v, const int p) {
	for (const auto& it : graph.edges(v)) {
		const int to = it.to();
		if (to == p) {
			continue;
		}
		dfs(to, v);
		if (cnt[to] > 0) {
			const int rem = total - cnt[to];
			const int up = min(rem, cnt[to]);
			dp[v] += dp[to] + up;
			cnt[v] += cnt[to];
		}
	}
	if (university[v]) {
		cnt[v] += 1;
	}
}

void solve(std::istream& in, std::ostream& out) {
	int n, k;
	in >> n >> k;
	graph = UndirectedGraph<int>(n);
	total = 2 * k;
	vector<int> u(total);
	cnt.assign(n, 0);
	dp.assign(n, 0);
	in >> u;
	university.assign(n, false);
	for (const auto& it : u) {
		university[it - 1] = true;
	}
	for (int i : range(n - 1)) {
		int from, to;
		in >> from >> to;
		--from, --to;
		graph.add_bidirectional_edge(from, to);
	}
	dfs(0, -1);
	out << dp[0] << endl;
}
