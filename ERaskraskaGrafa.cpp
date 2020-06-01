#include "base/header.hpp"
#include "graph/undirected_graph.hpp"
#include "collections/value_compressor.hpp"

class ERaskraskaGrafa {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		int a1, a2, a3;
		in >> n >> m >> a1 >> a2 >> a3;
		UndirectedGraph<int> graph(n);
		for (int i : range(m)) {
			int from, to;
			in >> from >> to;
			--from, --to;
			graph.add_bidirectional_edge(from, to);
		}
		std::vector<size_t> partition;
		if (!graph.is_bipartite(partition)) {
			out << "NO" << std::endl;
			return;
		}

		const auto components = compressed<int>(graph.labelled_components());

		const int colors = components.size();
		auto cnt = make_vector<int>(colors, 2, 0);
		for (int i : range(n)) {
			cnt[components[i]][partition[i]]++;
		}

		auto dp = make_vector<bool>(colors + 1, n + 1, false);
		dp[0][0] = true;

		for (int i : range(colors)) {
			for (int j : range(2)) {
				for (int x : range(n)) {
					if (dp[i][x]) {
						dp[i + 1][x + cnt[i][j]] = true;
					}
				}
			}
		}

		if (!dp[colors][a2]) {
			out << "NO" << std::endl;
			return;
		}

		std::vector<bool> fix_color(colors);
		int pos = a2;
		for (int i : downrange(colors)) {
			if (cnt[i][0] <= pos && dp[i][pos - cnt[i][0]]) {
				fix_color[i] = true;
				pos -= cnt[i][0];
			}
			else if (cnt[i][1] <= pos && dp[i][pos - cnt[i][1]]) {
				fix_color[i] = false;
				pos -= cnt[i][1];
			} else {
				assert(false);
			}
		}

		for (int i : range(n)) {
			if (fix_color[components[i]]) {
				partition[i] ^= 1;
			}
		}


		std::vector<int> ans;
		ans.reserve(n);
		for (int x : partition) {
			if (x == 0) {
				if (a1 > 0) {
					ans.emplace_back(1);
					--a1;
				} else {
					ans.emplace_back(3);
					--a3;
				}
			} else {
				ans.emplace_back(2);
			}
		}

		out << "YES" << std::endl;
		for (int x : ans) {
			out << x;
		}
		out << std::endl;
	}


	ERaskraskaGrafa() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
