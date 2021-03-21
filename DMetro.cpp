#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

class DMetro {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	int find_loop(const int v, const int p, const UndirectedGraph<>& graph, std::vector<bool>& is_loop, std::vector<int>& color) {
        color[v] = 1;
        for (const auto& edge : graph.edges(v)) {
            const int to = edge.to();
            if (to == p) {
                continue;
            }
            if (color[to] == 1) {
                color[v] = 2;
                is_loop[v] = true;
                return to;
            }
            if (color[to] == 0) {
                const int ret = find_loop(to, v, graph, is_loop, color);
                if (ret == -1) {
                    continue;
                }
                color[v] = 2;
                is_loop[v] = true;
                if (v == ret) {
                    return -1;
                }
                return ret;
            }
        }
        color[v] = 2;
        return -1;
	}

	void dfs(const int v, const int level, const UndirectedGraph<>& graph, std::vector<int>& dist) {
	    dist[v] = level;
	    for (const auto& edge : graph.edges(v)) {
            const int to = edge.to();
            if (dist[to] != -1) {
                continue;
            }
            dfs(to, level + 1, graph, dist);
	    }
	}

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        UndirectedGraph<> graph(n);
        for (int i : range(n)) {
            int x, y;
            in >> x >> y;
            --x, --y;
            graph.add_bidirectional_edge(x, y);
        }

        std::vector<int> color(n, 0);
        std::vector<bool> is_loop(n, false);
        find_loop(0, -1, graph, is_loop, color);

        std::vector<int> dist(n, -1);
        for (int v : range(n)) {
            if (is_loop[v]) {
                dist[v] = 0;
            }
        }
        for (int v : range(n)) {
            if (is_loop[v]) {
                dfs(v, 0, graph, dist);
            }
        }
        for (int x : dist) {
            out << x << " ";
        }
        out << std::endl;
	}


	DMetro() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
