#include "base/header.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/bridges.hpp"

class EDorogiVBertaune {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

    UndirectedGraph<int> graph;
    std::vector<int> direction;
    std::vector<int> last_edge;

    void dfs(const int v) {
        auto it = graph.edges(v).begin();
        int& index = last_edge[v];
        while (index < graph.edges_list(v).size()) {
            const int edge_id = graph.edges_list(v)[index++];
            const auto& edge = graph[edge_id];

            const int id = edge.id() / 2;
            if (direction[id] != -1) {
                continue;
            }
            const int mod = edge.id() % 2;
            direction[id] = mod;
            dfs(edge.to());
        }
    }

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;

        graph.init(n);
        for (int i : range(m)) {
            int x, y;
            in >> x >> y;
            --x, --y;
            graph.add_bidirectional_edge(x, y);
        }

        const GraphBridges bridges_constructor(graph);
        if (!bridges_constructor.bridges().empty()) {
            out << 0 << std::endl;
            return;
        }

        direction.assign(m, -1);
        last_edge.assign(n, 0);
        dfs(0);

        for (int i : range(m)) {
            const int id = i * 2 + direction[i];
#ifdef HOME
            out << graph.from(id) + 1 << " " << graph.to(id) + 1 << std::endl;
#else
            printf("%d %d\n", graph.from(id) + 1, graph.to(id) + 1);
#endif
        }
	}


	EDorogiVBertaune() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
