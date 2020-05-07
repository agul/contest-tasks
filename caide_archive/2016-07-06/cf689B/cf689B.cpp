#include "base/header.hpp"
#include "graph/directed_graph.hpp"
#include "queue.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	size_t n;
	in >> n;
	vector<int> a(n);
	in >> a;
	DirectedGraph<int> graph(n);
	for (int i = 0; i < n; ++i) {
		graph.add_directed_edge(i, a[i] - 1);
		if (i > 0) {
			graph.add_directed_edge(i - 1, i);
			graph.add_directed_edge(i, i - 1);
		}
	}
	vector<int> dp(n, INF);
	dp[0] = 0;
	Queue<int> q(n);
	q.push(0);
	while (!q.empty()) {
		const int v = q.pop_front();
		for (const auto& it : graph.edges(v)) {
			const int to = it.to();
			if (umin(dp[to], dp[v] + 1)) {
				q.push(to);
			}
		}
	}
	for (const auto& it : dp) {
		out << it << " ";
	}
	out << endl;
}
