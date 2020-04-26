#include "../algolib/cpplib/base/header.hpp"
#include "../algolib/cpplib/graph/undirected_graph.hpp"

class CLinovaIKorolevstvo {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int n, k;
		in >> n >> k;
		tree.init(n);
		for (int i : range(n - 1)) {
			int to, from;
			in >> from >> to;
			--from, --to;
			tree.add_bidirectional_edge(from, to);
		}

		dist = make_vector<int>(n, 0);
		children = make_vector<int>(n, 0);

		dfs(0, -1, 0);
		std::set<pii, std::greater<pii>> values;
		for (int i : range(n)) {
			values.emplace(dist[i] - children[i], i);
		}
		ll ans = 0;
		for (int i : range(k)) {
			const auto it = *values.begin();
			values.erase(values.begin());
			ans += it.first;
		}
		out << ans << std::endl;
	}

	int dfs(const int v, const int prev, const int cur_dist) {
		// std::cout << "DFS " << v << " " << prev << " " << cur_dist << std::endl;
		dist[v] = cur_dist;
		int& cur_children = children[v];
		cur_children = 0;
		for (const auto& edge : tree.edges(v)) {
			const int to = edge.to();
			if (to != prev) {
				cur_children += dfs(to, v, cur_dist + 1) + 1;
			}
		}
		return cur_children;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	UndirectedGraph<> tree;
	std::vector<int> dist;
	std::vector<int> children;
	size_t test_id_ = 0;
};
