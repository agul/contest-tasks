#include "base/header.hpp"
#include "graph/undirected_graph.hpp"
#include "collections/queue/queue.hpp"

class FConstructAPalindrome {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct Node {
	    int first;
	    int last;
	    int letter;
	};

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        UndirectedGraph<int, GraphType::Weighted> graph(n);

        for (int i : range(m)) {
            int x, y;
            char ch;
            in >> x >> y >> ch;
            graph.add_bidirectional_edge(x - 1, y - 1, ch + 1 - 'a');
        }
        // auto reversed = graph.reversed();

        auto dp = make_vector<int>(n, n, 27, INF);
        Queue<Node> q(n * n * 32);

        auto add = [&dp, &q](const int first, const int last, const int letter, const int len) {
            // debug(first, last, letter, len, dp[first][last][letter]);
            if (umin(dp[first][last][letter], len)) {
                // debug("ok");
                q.push(Node{first, last, letter});
            }
        };

        int ans = INF;
        add(0, n - 1, 0, 0);
        while (!q.empty()) {
            const int first = q.front().first;
            const int last = q.front().last;
            const int letter = q.front().letter;
            q.pop_front();
            const int len = dp[first][last][letter];

            // debug("GO", first, last, letter, len);
            if (first == last) {
                umin(ans, len);
            }

            if (letter == 0) {
                for (const auto& it : graph.edges(first)) {
                    const int to = it.to();
                    const int let = it.weight();
                    // debug(first, to, last, let, len + 1);
                    add(to, last, let, len + 1);
                }
            } else {
                for (const auto& it : graph.edges(last)) {
                    const int to = it.to();
                    const int let = it.weight();
                    // debug(first, to, last, let, len + 1);
                    if (let == letter) {
                        add(first, to, 0, len + 1);
                    }
                }
            }
        }
//        debug(dp[1][7][1]);
//        debug(dp[1][6][0]);
//        debug(dp[2][6][2]);
//        debug(dp[2][5][0]);
//        debug(dp[0][5][3]);
//        debug(dp[0][4][0]);
        if (ans == INF) {
            out << -1 << std::endl;
            return;
        }
        out << ans << std::endl;
	}


	FConstructAPalindrome() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
