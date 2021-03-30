#include "base/header.hpp"
#include "graph/directed_graph.hpp"

class ESkhema {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;

        std::vector<int> cnt(n, 0);
        std::vector<int> to(n);
        for (int i : range(n)) {
            int parent;
            in >> parent;

            to[i] = parent - 1;
            ++cnt[parent - 1];
        }

        std::vector<int> color(n, -1);
        int total_colors = 0;

        {
            std::vector<bool> used(n, false);
            auto get_color = [&color, &total_colors](const int v) {
                if (color[v] == -1) {
                    color[v] = total_colors++;
                }
                return color[v];
            };

            std::function<int(int)> dfs = [&to, &get_color, &dfs, &used, &color](const int v) {
                used[v] = true;
                const int next = to[v];
                if (used[next]) {
                    const int cur_color = get_color(next);
                    color[v] = cur_color;
                    return cur_color;
                }
                const int cur_color = dfs(next);
                color[v] = cur_color;
                return cur_color;
            };

            for (int v : range(n)) {
                if (!used[v]) {
                    dfs(v);
                }
            }
        }

        std::vector<int> any_v(total_colors);
        auto starters = make_vector<int>(total_colors, 0, 0);
        for (int v : range(n)) {
            if (cnt[v] == 0) {
                starters[color[v]].emplace_back(v);
            }
            any_v[color[v]] = v;
        }

        if (total_colors == 1 && starters.front().empty()) {
            out << 0 << std::endl;
            return;
        }

        for (int i : range(total_colors)) {
            if (starters[i].empty()) {
                starters[i].emplace_back(any_v[i]);
            }
        }



        std::vector<int> any_loop_v(total_colors);
        {
            std::vector<bool> used(n, false);
            std::function<int(int)> find_loop = [&to, &used, &find_loop](const int v) {
                used[v] = true;
                const int next = to[v];
                if (used[next]) {
                    return next;
                }
                return find_loop(next);
            };

            for (int i : range(total_colors)) {
                any_loop_v[i] = find_loop(any_v[i]);
            }
        }





        std::vector<pii> ans;
        for (int i : range(total_colors)) {
            const int prev = (i - 1 + total_colors) % total_colors;
            const int prev_loop_v = any_loop_v[prev];
            for (int x : starters[i]) {
                ans.emplace_back(prev_loop_v, x);
            }
        }


        out << ans.size() << std::endl;
        for (const auto& it : ans) {
            out << it.first + 1 << " " << it.second + 1 << std::endl;
        }
	}


	ESkhema() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
