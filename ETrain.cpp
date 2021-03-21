#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

class ETrain {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m, x, y;
        in >> n >> m >> x >> y;
        --x;
        --y;

        UndirectedGraph<ll, GraphType::Weighted> graph(n);
        std::vector<ll> start_times;
        for (int i : range(m)) {
            int from, to, len, start_time;
            in >> from >> to >> len >> start_time;
            --from;
            --to;
            start_times.emplace_back(start_time);
            start_times.emplace_back(start_time);
            graph.add_bidirectional_edge(from, to, len);
        }

        std::vector<ll> dist(n, LINF);
        dist[x] = 0;
        using QueueNode = std::pair<ll, size_t>;
        std::priority_queue<QueueNode> q;
        q.emplace(0, x);
        while (!q.empty()) {
            const QueueNode node = q.top();
            q.pop();
            const ll len = -node.first;
            const size_t vertex = node.second;
            if (len > dist[vertex]) {
                continue;
            }
            for (const auto& it : graph.edges(vertex)) {
                const ll K = start_times[it.id()];
                const ll new_dist = (len == 0 ? 0 : ((len - 1) / K + 1) * K) + it.weight();
                const size_t to = it.to();
                if (umin(dist[to], new_dist)) {
                    q.push(std::make_pair(-new_dist, to));
                }
            }
        }
        if (dist[y] == LINF) {
            out << -1 << std::endl;
            return;
        }
        out << dist[y] << std::endl;
	}


	ETrain() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
