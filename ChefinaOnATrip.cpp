#include "base/header.hpp"
#include "graph/lca.hpp"
#include "graph/undirected_graph.hpp"

class ChefinaOnATrip {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, q;
		in >> n >> q;
		UndirectedGraph<int> graph(n);
		for (int i : range(n - 1)) {
			int from, to;
			in >> from >> to;
			graph.add_bidirectional_edge(from - 1, to - 1);
		}
		std::vector<int> heights(n);
		in >> heights;

		size_t starting_vertex = (max_element(heights) - heights.cbegin());
		LCA lca(graph, starting_vertex);

		std::vector<size_t> start_decrease(n);
		std::iota(all(start_decrease), 0);
		std::function<void(const size_t, const size_t, const size_t)> dfs_decrease = [&graph, &start_decrease, &heights, &dfs_decrease](const size_t v, const size_t prev, const size_t sdv) {
			start_decrease[v] = sdv;
			for (const auto& edge : graph.edges(v)) {
				const int to = edge.to();
				if (to == prev) {
					continue;
				}
				int next_sdv = sdv;
				if (heights[to] >= heights[v]) {
					next_sdv = to;
				}
				dfs_decrease(to, v, next_sdv);
			}
		};

		std::vector<size_t> start_increase(n);
		std::iota(all(start_increase), 0);
		std::function<void(const size_t, const size_t, const size_t)> dfs_increase = [&graph, &start_increase, &heights, &dfs_increase](const size_t v, const size_t prev, const size_t sdv) {
			start_increase[v] = sdv;
			for (const auto& edge : graph.edges(v)) {
				const int to = edge.to();
				if (to == prev) {
					continue;
				}
				int next_sdv = sdv;
				if (heights[to] <= heights[v]) {
					next_sdv = to;
				}
				dfs_increase(to, v, next_sdv);
			}
		};

		dfs_decrease(starting_vertex, starting_vertex, starting_vertex);
		dfs_increase(starting_vertex, starting_vertex, starting_vertex);

		std::string ans;
		ans.reserve(q);
		for (int _ : range(q)) {
			int from, to;
			in >> from >> to;
			--from, --to;

			const int parent = lca.query(from, to);
			const int decrease_from = start_decrease[from];
			const int decrease_to = start_decrease[to];
			debug(parent, decrease_from, decrease_to);

			bool ok = false;
			ok |= (lca.upper(decrease_from, parent) && (lca.upper(decrease_to, parent) || lca.upper(start_increase[decrease_to], parent)));
			ok |= (lca.upper(decrease_to, parent) && (lca.upper(decrease_from, parent) || lca.upper(start_increase[decrease_from], parent)));

			ans += (ok ? '1' : '0');
		}
		out << ans << std::endl;
	}


	ChefinaOnATrip() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
