#include "base/header.hpp"
#include "graph/directed_graph.hpp"

class BPorosyataIVolki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<std::string> field(n);
        in >> field;

        DirectedGraph<> graph(n * m);
        for (int i : range(n)) {
            for (int j : range(m)) {
                if (field[i][j] != 'W') {
                    continue;
                }
                for (int dir : range(4)) {
                    const int x = i + DX[dir];
                    const int y = j + DY[dir];
                    if (x < 0 || y < 0 || x >= n || y >= m || field[x][y] != 'P') {
                        continue;
                    }
                    graph.add_directed_edge(x * m + y, i * m + j);
                }
            }
        }
        std::vector<size_t> match;
        graph.maximal_matching(&match);
        int ans = 0;
        debug(match);
        for (int i : range(n * m)) {
            if (match[i] < n * m) {
                ++ans;
                debug(i, match[i]);
            }
        }
        out << ans << std::endl;
	}


	BPorosyataIVolki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
