#include "base/header.hpp"
#include "graph/directed_graph.hpp"

class DPrekrasnayaMatritsa {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct Column {
	    int cnt;
	    int id;

	    pii as_pair() const {
	        return {cnt, id};
	    }

	    bool operator<(const Column& rhs) const {
            return as_pair() < rhs.as_pair();
	    }
	};

	void solve_greedy(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        auto a = make_vector<pii>(n, 0, pii{0, 0});
        std::vector<int> column_cnt(m, 0);
        for (int i : range(n)) {
            std::vector<pii>& values = a[i];
            for (int j : range(m)) {
                int x;
                in >> x;
                if (x == -1) {
                    continue;
                }
                values.emplace_back(x, j);
                ++column_cnt[j];
            }
            sort(values);
        }

        std::vector<Column> all_columns;
        std::set<Column> columns;
        for (int j : range(m)) {
            all_columns.emplace_back(Column{column_cnt[j], j});
            columns.emplace(all_columns.back());
        }

        auto decrease = [&columns, &all_columns](const int col_id) {
            Column& column = all_columns[col_id];
            columns.erase(column);
            column.cnt -= 1;
            columns.emplace(column);
        };

        std::vector<int> current_pointer(n, 0);
        std::vector<SafeUnorderedSet<int>> min_cols(n);
        std::vector<int> ans;
        for (int column_id : range(m)) {
            for (int i : range(n)) {
                int& id = current_pointer[i];
                if (id >= a[i].size()) {
                    continue;
                }
                if (min_cols[i].empty()) {
                    const int cur_value = a[i][id].first;
                    while (id < a[i].size() && a[i][id].first == cur_value) {
                        const int col_id = a[i][id].second;
                        min_cols[i].emplace(col_id);
                        decrease(col_id);
                        ++id;
                    }
                }
            }
            if (columns.empty() || columns.begin()->cnt != 0) {
                out << -1 << std::endl;
                return;
            }
            const int selected_column = columns.begin()->id;
            columns.erase(all_columns[selected_column]);
            for (int i : range(n)) {
                min_cols[i].erase(selected_column);
            }
            ans.emplace_back(selected_column);
        }
        for (int x : ans) {
            out << x + 1 << " ";
        }
        out << std::endl;
	}

    void solve_graph(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        DirectedGraph<> graph(m + n * m * 2);
        int vertex_id = m;
        for (int i : range(n)) {
            std::vector<pii> values;
            for (int j : range(m)) {
                int x;
                in >> x;
                if (x == -1) {
                    continue;
                }
                values.emplace_back(x, j);
            }
            sort(values);
            int index = 0;
            while (index < values.size()) {
                const int cur_value = values[index].first;
                int prev_vertex = vertex_id++;
                int cur_vertex = vertex_id;
                while (index < values.size() && cur_value == values[index].first) {
                    graph.add_directed_edge(prev_vertex, values[index].second);
                    graph.add_directed_edge(values[index].second, cur_vertex);
                    ++index;
                }
            }
            ++vertex_id;
        }
        std::vector<size_t> order;
        if (!graph.top_sort_acyclic(&order)) {
            out << -1 << std::endl;
            return;
        }
        for (int x : order) {
            if (x < m) {
                out << x + 1 << " ";
            }
        }
        out << std::endl;
	}

    void solve(std::istream& in, std::ostream& out) {
	    solve_graph(in, out);
	}

	DPrekrasnayaMatritsa() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
