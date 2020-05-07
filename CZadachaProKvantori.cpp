#include "base/header.hpp"
#include "graph/directed_graph.hpp"

class CZadachaProKvantori {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		DirectedGraph<int> graph(n);

		for (int i : range(m)) {
			int from, to;
			in >> from >> to;
			--from, --to;
			graph.add_directed_edge(from, to);
		}

		if (!graph.is_acyclic()) {
			out << -1 << std::endl;
			return;
		}

		const auto reversed = graph.reversed();

		auto quantor = make_vector<bool>(n, false);
		auto used_forward = make_vector<bool>(n, false);
		auto used_backward = make_vector<bool>(n, false);

		std::function<void(int, const DirectedGraph<int>&, std::vector<bool>&)> dfs = [&dfs](const int v, const DirectedGraph<int>& graph, std::vector<bool>& used) {
			if (used[v]) {
				return;
			}
			used[v] = true;
			for (const auto& edge : graph.edges(v)) {
				const int to = edge.to();
				dfs(to, graph, used);
			}
		};

		for (auto v : graph.vertices()) {
			if (!used_forward[v] && !used_backward[v]) {
				quantor[v] = true;
			}
			dfs(v, graph, used_forward);
			dfs(v, reversed, used_backward);
		}

		std::string ans;
		for (int i : range(n)) {
			ans += (quantor[i] ? 'A' : 'E');
		}
		const int ans_cnt = std::count(all(ans), 'A');

		out << ans_cnt << std::endl << ans << std::endl;
	}

	static constexpr bool kUseCustomChecker = true;
	bool check(std::string input, std::string expected_output, std::string actual_output) {
		std::istringstream jury(expected_output);
		std::istringstream participant(actual_output);

		int jans, pans;
		jury >> jans;
		participant >> pans;

		return jans == pans;
	}

	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
