#include "base/header.hpp"
#include "graph/directed_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	DirectedGraph<int> graph(n);
	for (int i : range(m)) {
		int x, y;
		in >> x >> y;
		--x, --y;
		graph.add_directed_edge(x, y);
	}
	std::vector<size_t> color;
	const size_t components_count = graph.scc(&color);
	std::vector<size_t> cnt(components_count);
	for (const auto& it : color) {
		++cnt[it];
	}
	std::vector<size_t> min_loop(components_count, INF);
	Queue<size_t> q(n * 2);
	for (const auto& v : graph.vertices()) {
		const size_t component = color[v];
		if (cnt[component] == 1) {
			min_loop[component] = 0;
			continue;
		}
		q.clear();
		q.push(v);
		std::vector<size_t> dist(n, INF);
		while (!q.empty()) {
			const size_t vertex = q.pop_front();
			size_t len = dist[vertex];
			if (vertex == v && len == INF) {
				len = 0;
			}
			for (const auto& it : graph.edges(vertex)) {
				const size_t to = it.to();
				if (color[to] != component || !umin(dist[to], len + 1)) {
					continue;
				}
				q.push(to);
			}
		}
		umin(min_loop[component], dist[v]);
	}
	std::vector<std::pair<size_t, size_t>> vertices;
	for (size_t i = 0; i < n; ++i) {
		vertices.emplace_back(color[i], i);
	}
	sort(vertices.rbegin(), vertices.rend());
	for (const auto& it : vertices) {
		const size_t v = it.second;
		const size_t component = color[v];
		if (min_loop[component] == 0) {
			continue;
		}
		for (const auto& it : graph.edges(v)) {
			const size_t to = it.to();
			if (color[to] == component) {
				continue;
			}
			min_loop[component] = 0;
			break;
		}
	}
	const size_t loop_len = std::accumulate(min_loop.begin(), min_loop.end(), 0) * 998;
	const size_t loop_cnt = min_loop.size() - std::count(min_loop.begin(), min_loop.end(), 0);
	const size_t ans = loop_len + n + loop_cnt;
	out << ans << endl;
}



/* vvi graph;
bool used[MAXN];
int cnt[MAXN], ans;

const int MAGIC = 1000;

void dfs(int v) {
++cnt[v];
++ans;
if (cnt[v] < MAGIC) {
for (const auto& it : graph[v]) {
if (!used[it]) {
dfs(it);
}
break;
}
}
used[v] = true;
}

void solve(std::istream& in, std::ostream& out) {
int n, m;
in >> n >> m;
graph.clear();
graph.resize(n);
for (int i = 0; i < m; ++i) {
int x, y;
in >> x >> y;
--x, --y;
graph[x].emplace_back(y);
}
fill(used, 0);
fill(cnt, 0);
ans = 0;
for (int i = 0; i < n; ++i) {
if (!used[i]) {
dfs(i);
}
}
out << ans << endl;
} */