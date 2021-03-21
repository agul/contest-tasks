#include "base/header.hpp"
#include "graph/undirected_graph.hpp"
#include "collections/stack/stack.hpp"

class FUnichtozhenieReber {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	bool find_eulerian_path(const int starting_vertex, std::vector<std::unordered_multiset<int>>& graph, std::vector<int>& path) {
	    const int n = graph.size();

	    std::vector<int> degree(n, 0);
	    std::vector<int> odd_vertices;
	    for (int i : range(n)) {
            degree[i] = graph[i].size();
            if (degree[i] % 2 == 1) {
                odd_vertices.emplace_back(i);
            }
	    }

	    if (!odd_vertices.empty() && odd_vertices.size() != 2) {
	        return false;
	    }

	    if (!odd_vertices.empty()) {
	        ++degree[odd_vertices.front()];
	        ++degree[odd_vertices.back()];

	        graph[odd_vertices.front()].emplace(odd_vertices.back());
            graph[odd_vertices.back()].emplace(odd_vertices.front());
	    }

	    // debug("OK");

	    const int edges_count = std::accumulate(all(degree), 0);

        auto delete_edge = [&graph, &degree](const int from, const int to) {
            const auto it = graph[from].find(to);
            if (it != graph[from].cend()) {
                graph[from].erase(it);
            }
            const auto jt = graph[to].find(from);
            if (jt != graph[to].cend()) {
                graph[to].erase(jt);
            }

            degree[from] -= 1;
            degree[to] -= 1;
        };

        debug(edges_count);
        Stack<int> stack(edges_count * 4 + n);
        stack.push(starting_vertex);
        while (!stack.empty()) {
            const int v = stack.top();
            debug(v, degree[v], graph[v]);
            if (degree[v] == 0) {
                stack.pop();
                path.emplace_back(v);
                continue;
            }

            const int to = *graph[v].begin();
            delete_edge(v, to);
            stack.push(to);
        }

        for (int i : range(n)) {
            if (!graph[i].empty()) {
                return false;
            }
        }

        if (!odd_vertices.empty()) {
            std::vector<int> adjusted_path;

            for (int i : range(path.size() - 1)) {
                const int cur = path[i];
                const int next = path[i + 1];
                if (cur == odd_vertices.front() && next == odd_vertices.back() || cur == odd_vertices.back() && next == odd_vertices.front()) {
                    for (int j : range<int>(i + 1, path.size())) {
                        adjusted_path.emplace_back(path[j]);
                    }
                    for (int j : inclusiveRange<int>(1, i)) {
                        adjusted_path.emplace_back(path[j]);
                    }
                    path.swap(adjusted_path);
                    break;
                }
            }
        }

        return true;
	}

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;

        std::vector<int> degree(n, 0);
        UndirectedGraph<> graph(n);
        for (int i : range(m)) {
            int from, to;
            in >> from >> to;
            graph.add_bidirectional_edge(from - 1, to - 1);
            ++degree[from - 1];
            ++degree[to - 1];
        }

        // debug("START");
        for (int switch_point : range(-1, n)) {

            std::vector<int> visitors;
            std::vector<std::unordered_multiset<int>> tmp_graph(n);
            // debug("GO", switch_point);

            for (const auto& it : graph.edges()) {
                if (it.from() == switch_point && degree[it.to() == 1]) {
                    visitors.emplace_back(it.to());
                    continue;
                }
                if (it.to() == switch_point && degree[it.from()] == 1) {
                    // visitors.emplace_back(it.from());
                    continue;
                }
                tmp_graph[it.from()].emplace(it.to());
            }

            std::vector<int> path;
            if (!find_eulerian_path(std::max(switch_point, 0), tmp_graph, path)) {
                continue;
            }

            path.emplace_back(-2);
            for (const auto& x : visitors) {
                path.emplace_back(x);
                path.emplace_back(switch_point);
            }

            out << path.size() << std::endl;
            for (const auto& x : path) {
                out << x + 1 << " ";
            }
            out << std::endl;
            return;
        }
        out << 0 << std::endl;
	}


	FUnichtozhenieReber() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
