#include "Head.h"
#include "graph/graph.hpp"
#include "range/ranges.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 222222;

int deg[MAXN];
ll x, y, n, cnt;
UndirectedGraph graph(MAXN, MAXN);

bool is_sun() {
	for (int i : range(n)) {
		if (deg[i] == n - 1) {
			return true;
		}
	}
	return false;
}

int dfs(int v, int p) {
	int sum = 0;
	for (const auto& it : graph.edges[v]) {
		int to = graph.to[it];
		if (to != p) {
			sum += dfs(to, v);
		}
	}
	if (sum < 2) {
		return 1;
	}
	cnt += sum - 1;
	return 0;
}

void solve(istream& ins, ostream& out) {
	ins >> n >> x >> y;
	graph.clear();
	graph.initGraph(n);
	fill(deg, 0);
	for (int i : range(1LL, n)) {
		int from, to;
		ins >> from >> to;
		--from, --to;
		graph.addBidirectionalEdge(from, to);
		++deg[from];
		++deg[to];
	}
	if (n == 2) {
		out << x << endl;
		return;
	}
	if (is_sun()) {
		out << min(x + y * (n - 2), x * 2 + y * (n - 3)) << endl;
		return;
	}
	if (x >= y) {
		out << y * (n - 1) << endl;
		return;
	}
	cnt = 0;
	cnt += dfs(0, -1);
	out << x * (n - cnt) + y * (cnt - 1) << endl;
}
