#include "base/header.hpp"
#include "graph/dsu.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

using G = UndirectedGraph<ll, GraphType::Weighted>;

G graph;
vector<bool> alive, used;
vector<int> fup, tin;
int timer;

bool find_path(const int v, const int t, std::vector<int>& path) {
	if (v == t) {
		return true;
	}
	used[v] = true;
	for (const auto& it : graph.edges(v)) {
		const int to = it.to();
		const int id = it.id();
		if (!alive[id]) {
			continue;
		}
		path.emplace_back(id);
		if (!used[to] && find_path(to, t, path)) {
			return true;
		}
		path.pop_back();
	}
	return false;
}

void find_bridges(const int v, const int p, std::vector<int>& all_edges, std::unordered_set<int>& bridges) {
	used[v] = true;
	tin[v] = timer;
	fup[v] = timer;
	++timer;
	for (const auto& it : graph.edges(v)) {
		if (!alive[it.id()] || it.id() == (p ^ 1)) {
			continue;
		}
		all_edges.emplace_back(it.id());
		const size_t to = it.to();
		if (used[to]) {
			umin(fup[v], tin[to]);
		} else {
			find_bridges(to, it.id(), all_edges, bridges);
			umin(fup[v], fup[to]);
			if (fup[to] > tin[v]) {
				bridges.emplace(it.id());
			}
		}
	}
}

void solve(std::istream& in, std::ostream& out) {
	int n, m, s, t;
	in >> n >> m >> s >> t;
	graph = G(n);
	for (int i : range(m)) {
		int from, to, weight;
		in >> from >> to >> weight;
		--from, --to;
		graph.add_bidirectional_edge(from, to, weight);
	}
	--s, --t;
	vector<int> path, tmp_path;
	path.reserve(n);
	tmp_path.reserve(n);
	alive.assign(m * 2, true);
	used.assign(n, false);
	if (!find_path(s, t, path)) {
		out << 0 << endl << 0 << endl;
		return;
	}
	DSU dsu;
	ll ans = LINF;
	std::vector<int> edges, all_edges;
	std::unordered_set<int> bridges;
	for (const auto& id : path) {
		dsu.init(n);
		alive[id] = false;
		alive[id ^ 1] = false;
		for (const auto& it : graph.edges()) {
			if (!alive[it.id()]) {
				continue;
			}
			dsu.unite(it.from(), it.to());
		}
		if (dsu.find_set(s) != dsu.find_set(t)) {
			if (umin(ans, graph.weight(id))) {
				edges = { id };
			}
			alive[id] = true;
			alive[id ^ 1] = true;
			continue;
		}

		all_edges.clear();
		bridges.clear();
		fup.assign(n, -1);
		tin.assign(n, -1);
		timer = 0;
		used.assign(n, false);
		find_bridges(s, -1, all_edges, bridges);
		used.assign(n, false);
		tmp_path.clear();
		find_path(s, t, tmp_path);
		alive[id] = true;
		alive[id ^ 1] = true;

		for (const auto& it : tmp_path) {
			if (!bridges.count(it) && !bridges.count(it ^ 1)) {
				continue;
			}
			if (umin(ans, graph.weight(id) + graph.weight(it))) {
				edges = { id, it };
			}
		}
	}
	if (ans == LINF) {
		out << -1 << endl;
		return;
	}
	out << ans << endl;
	out << edges.size() << endl;
	for (const auto& it : edges) {
		out << it / 2 + 1 << " ";
	}
	out << endl;
}
