#include "../algolib/cpplib/base/header.hpp"
#include "../algolib/cpplib/graph/undirected_graph.hpp"

class DNaznachenieVesovRebram {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		graph.init(n);
		for (int i : range(n - 1)) {
			int x, y;
			in >> x >> y;
			--x, --y;
			graph.add_bidirectional_edge(x, y);
		}
		if (n == 2) {
			out << "1 1" << std::endl;
			return;
		}

		levels = make_vector<int>(n, 0);
		max_ans = n - 1;
		const int root = graph.find_vertex_with_max_degree();
		dfs(root, -1, 0);

		int min_ans = 1;
		bool odd = false;
		bool even = false;
		for (int v : graph.vertices()) {
			if (graph.edges(v).size() == 1) {
				odd |= (levels[v] & 1);
				even |= (levels[v] & 1) ^ 1;
			}
		}
		if (odd && even) {
			min_ans = 3;
		}

		out << min_ans << " " << max_ans << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}

	int dfs(int v, int prev, int level) {
		levels[v] = level;
		int leaf_children = 0;
		for (const auto& edge : graph.edges(v)) {
			if (edge.to() != prev) {
				leaf_children += dfs(edge.to(), v, level + 1);
			}
		}
		max_ans -= std::max(0, leaf_children - 1);
		return (graph.edges(v).size() == 1 ? 1 : 0);
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;

	int max_ans;
	UndirectedGraph<> graph;
	std::vector<int> levels;
};
