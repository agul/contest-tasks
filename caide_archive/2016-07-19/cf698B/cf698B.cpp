#include "base/header.hpp"
#include "graph/directed_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<int> p(n);
	in >> p;
	for (auto& it : p) {
		--it;
	}
	vector<int> a = p;

	int root = -1;
	for (int i : range(n)) {
		if (i == p[i]) {
			root = i;
			break;
		}
	}

	DirectedGraph<int> graph(n);
	for (int i : range(n)) {
		if (p[i] == i) {
			continue;
		}
		graph.add_directed_edge(i, p[i]);
	}

	std::vector<size_t> col;
	const size_t comp_cnt = graph.scc(&col);

	std::vector<int> cnt(comp_cnt);
	std::vector<bool> used(comp_cnt);

	for (const auto& it : col) {
		++cnt[it];
	}

	for (int i : range(n)) {
		const size_t color = col[i];
		if (used[color] || cnt[color] == 1) {
			continue;
		}
		a[i] = i;
		used[color] = true;
	}

	std::vector<size_t> roots;
	for (int i : range(n)) {
		if (a[i] == i) {
			roots.emplace_back(i);
		}
	}
	if (root == -1) {
		root = roots.front();
	}

	for (const auto& it : roots) {
		a[it] = root;
	}


	int ans = 0;
	for (int i : range(n)) {
		ans += (a[i] != p[i] ? 1 : 0);
	}
	out << ans << endl;
	for (const auto& it : a) {
		out << it + 1 << " ";
	}
	out << endl;
}
