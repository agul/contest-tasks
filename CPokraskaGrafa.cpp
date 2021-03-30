#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

class CPokraskaGrafa {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        UndirectedGraph<int, GraphType::Weighted> graph(n);
        for (int i : range(m)) {
            int x, y;
            char color;
            in >> x >> y >> color;
            graph.add_bidirectional_edge(x - 1, y - 1, (color == 'R' ? 1 : 0));
        }


        std::vector<std::vector<int>> ans;
        for (int target_color : range(2)) {
            std::vector<int> used(n, 0);
            std::vector<int> vertex_switched(n, 0);
            int timer = 0;

            std::function<bool(int, int, std::vector<int>&, std::vector<int>&)> dfs = [&graph, &used, &dfs, &timer, &vertex_switched, &target_color](const int v, const int switch_vertex, std::vector<int>& switched, std::vector<int>& not_switched) {
                used[v] = timer;
                vertex_switched[v] = switch_vertex;
                (switch_vertex ? switched : not_switched).emplace_back(v);

                for (const auto& it : graph.edges(v)) {
                    const int to = it.to();
                    const int initial_color = it.weight();
                    if (used[to] == timer) {
                        if ((initial_color ^ switch_vertex ^ vertex_switched[to]) != target_color) {
                            return false;
                        }
                        continue;
                    }
                    const int cur_color = (initial_color ^ switch_vertex);
                    const int switch_next_vertex = (target_color ^ cur_color);
                    if (!dfs(to, switch_next_vertex, switched, not_switched)) {
                        return false;
                    }
                }
                return true;
            };

            bool ok = true;
            std::vector<int> cur_ans;
            for (int v : range(n)) {
                if (!used[v]) {
                    std::vector<int> best;
                    bool any = false;
                    for (int need_to_switch : range(2)) {
                        std::vector<int> switched, not_switched;
                        ++timer;
                        if (!dfs(v, need_to_switch, switched, not_switched)) {
                            continue;
                        }
                        any = true;
                        if (switched.size() > not_switched.size()) {
                            switched.swap(not_switched);
                        }
                        if (best.empty() || best.size() > switched.size()) {
                            best.swap(switched);
                        }
                    }
                    if (!any) {
                        ok = false;
                        break;
                    }
                    std::copy(all(best), std::back_inserter(cur_ans));
                }
            }
            if (!ok) {
                continue;
            }
            ans.emplace_back(cur_ans);
        }
        if (ans.empty()) {
            out << -1 << std::endl;
            return;
        }
        if (ans.size() > 1 && ans.front().size() < ans.back().size()) {
            ans.front().swap(ans.back());
        }
        out << ans.back().size() << std::endl;
        for (int x : ans.back()) {
            out << x + 1 << " ";
        }
        out << std::endl;
	}


	CPokraskaGrafa() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
