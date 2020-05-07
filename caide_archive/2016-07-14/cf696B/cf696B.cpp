#include "base/header.hpp"
#include "graph/directed_graph.hpp"
#include "maths/permutation.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

/* DirectedGraph<int> graph;
vector<vector<int>> values;
int timer;

void dfs(int v) {
	values[v].emplace_back(++timer);
	Permutation<int> p(0);
	for (const auto& it : graph.edges(v)) {
		p.emplace_back(it.id());
	}
	int init_timer = timer;
	do {
		timer = init_timer;
		for (const auto& it : p) {
			dfs(graph.to(it));
		}
	} while (p.next());
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	graph = DirectedGraph<int>(n);
	for (int i : range(1, n)) {
		int x;
		in >> x;
		graph.add_directed_edge(x - 1, i);
	}
	values.clear();
	values.resize(n);
	timer = 0;
	dfs(0);
	for (const auto& it : values) {
		int sum = std::accumulate(all(it), 0);
		out << static_cast<double>(sum) / it.size() << " ";
	}
	out << endl;
} */


DirectedGraph<int> graph;
vector<int> children;
vector<double> ans;

int count_child(const int v) {
	children[v] = 1;
	for (const auto& it : graph.edges(v)) {
		children[v] += count_child(it.to());
	}
	return children[v];
}

void dfs(const int v) {
	int sum = 0;
	for (const auto& it : graph.edges(v)) {
		sum += children[it.to()];
	}
	for (const auto& it : graph.edges(v)) {
		const int to = it.to();
		ans[to] = ans[v] + (sum - children[to]) / 2.0 + 1;
		dfs(to);
	}
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	graph = DirectedGraph<int>(n);
	for (int i : range(1, n)) {
		int x;
		in >> x;
		graph.add_directed_edge(x - 1, i);
	}
	children.assign(n, 0);
	count_child(0);
	ans.assign(n, 0);
	ans[0] = 1;
	dfs(0);
	for (const auto& it : ans) {
		out << it << " ";
	}
	out << endl;
}