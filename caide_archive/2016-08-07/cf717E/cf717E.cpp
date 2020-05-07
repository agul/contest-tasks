#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

UndirectedGraph<int> graph;
vector<int> colors;
vector<bool> subtree;

bool check_subtrees(const int v, const int p) {
	bool res = (colors[v] == -1);
	for (const auto& it : graph.edges(v)) {
		const int to = it.to();
		if (to == p) {
			continue;
		}
		res |= check_subtrees(to, v);
	}
	return subtree[v] = res;
}

void dfs(const int v, const int p, std::vector<int>& path) {
	auto mark = [&](const int v) {
		path.emplace_back(v);
		colors[v] = -colors[v];
	};
	if (v == 0) {
		path.emplace_back(0);
	}
	else {
		mark(v);
	}
	bool any = false;
	for (const auto& it : graph.edges(v)) {
		const int to = it.to();
		if (to == p || !subtree[to]) {
			continue;
		}
		if (any) {
			mark(v);
		}
		any = true;
		dfs(to, v, path);
	}
	if (any) {
		if (v == 0 && colors[v] == 1) {
			return;
		}
		mark(v);
	}
	if (colors[v] == -1) {
		if (v == 0) {
			for (const auto& it : graph.edges(v)) {
				const int to = it.to();
				mark(to);
				mark(v);
				mark(to);
			}
			return;
		}
		mark(p);
		mark(v);
	}
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	colors.assign(n, 0);
	in >> colors;
	graph = UndirectedGraph<int>(n);
	for (int i : range(n - 1)) {
		int from, to;
		in >> from >> to;
		graph.add_bidirectional_edge(from - 1, to - 1);
	}
	subtree.assign(n, false);
	check_subtrees(0, -1);
	if (!subtree[0]) {
		out << 1 << endl;
		return;
	}
	vector<int> path;
	dfs(0, -1, path);
	for (const auto& it : path) {
		out << it + 1 << " ";
	}
	out << endl;
}
