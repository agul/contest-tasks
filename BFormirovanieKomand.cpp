#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

class BFormirovanieKomand {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	std::vector<bool> used;
    UndirectedGraph<> graph;

    int find_len(const int v, const int p) {
        used[v] = true;
        for (const auto& it : graph.edges(v)) {
            const int to = it.to();
            if (!used[to]) {
                return find_len(to, v) + 1;
            }
        }
        return 1;
    }

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        graph.init(n);
        for (int i : range(m)) {
            int x, y;
            in >> x >> y;
            graph.add_bidirectional_edge(x - 1, y - 1);
        }

        int none = 0;

        used.assign(n, false);
        for (int v : range(n)) {
            if (graph.edges(v).size() == 0) {
                ++none;
                used[v] = true;
            }
        }

        int odd_chain = 0;
        for (int v : range(n)) {
            if (graph.edges(v).size() == 1 && !used[v]) {
                const int len = find_len(v, -1);
                if (len % 2 == 1) {
                    ++odd_chain;
                }
            }
        }

        int odd_loop = 0;
        for (int v : range(n)) {
            if (!used[v]) {
                const int len = find_len(v, -1);
                if (len % 2 == 1) {
                    ++odd_loop;
                }
            }
        }

        int ans = odd_loop;

        odd_chain %= 2;
        none %= 2;

        ans += (odd_chain + none) % 2;

        out << ans << std::endl;
	}


	BFormirovanieKomand() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
