#include "base/header.hpp"
#include "graph/directed_graph.hpp"

class CPrazdnik {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        DirectedGraph<> graph(n);
        std::vector<int> roots;
        for (int i : range(n)) {
            int x;
            in >> x;
            if (x == -1) {
                roots.emplace_back(i);
            } else {
                graph.add_directed_edge(x - 1, i);
            }
        }

        std::function<int(int)> dfs = [&graph, &dfs](const int v) {
            int ret = 0;
            for (const auto& edge : graph.edges(v)) {
                umax(ret, dfs(edge.to()));
            }
            return ret + 1;
        };
        int ans = 0;
        for (int v : roots) {
            umax(ans, dfs(v));
        }
        out << ans << std::endl;
	}


	CPrazdnik() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
