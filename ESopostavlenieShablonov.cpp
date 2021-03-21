#include "base/header.hpp"
#include "graph/directed_graph.hpp"

class ESopostavlenieShablonov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	const int kMaxn = 555555;

	static std::vector<int> string_to_ints(const std::string& t) {
	    std::vector<int> a;
	    for (const char ch : t) {
	        if (ch == '_') {
	            a.emplace_back(0);
	        } else {
	            a.emplace_back(ch - 'a' + 1);
	        }
	    }
	    return a;
	}

	static int template_to_int(const std::vector<int>& ints) {
	    int ret = 0;
	    for (int i : reversed(ints)) {
	        ret = ret * 27 + i;
	    }
	    return ret;
	}

	void solve(std::istream& in, std::ostream& out) {
        int n, m, k;
        in >> n >> m >> k;
        std::vector<int> template_to_index(kMaxn, -1);
        for (int i : range(n)) {
            std::string t;
            in >> t;
            const auto chars = string_to_ints(t);
            const int id = template_to_int(chars);
            template_to_index[id] = i;
        }

        auto add = [&template_to_index](const int id, std::vector<int>& existing_templates) {
            const int index = template_to_index[id];
            if (index != -1) {
                existing_templates.emplace_back(index);
            }
        };

        DirectedGraph<int> g(n);

        for (int i : range(m)) {
            int mt;
            std::string t;
            in >> t >> mt;
            --mt;

            auto chars = string_to_ints(t);

            std::vector<int> existing_templates;
            add(template_to_int(chars), existing_templates);

            for (int& x : chars) {
                int tmp = 0;
                std::swap(x, tmp);
                add(template_to_int(chars), existing_templates);
                std::swap(x, tmp);
            }

            for (int x : range(k)) {
                int tmpx = chars[x];
                chars[x] = 0;
                for (int y : range(x + 1, k)) {
                    int tmpy = chars[y];
                    chars[y] = 0;
                    add(template_to_int(chars), existing_templates);
                    chars[y] = tmpy;
                }
                chars[x] = tmpx;
            }

            for (int x : range(k)) {
                std::vector<int> tmp_vec(k, 0);
                tmp_vec[x] = chars[x];
                add(template_to_int(tmp_vec), existing_templates);
            }

            add(0, existing_templates);

            const auto it = std::find(all(existing_templates), mt);
            if (it == existing_templates.cend()) {
                out << "NO" << std::endl;
                return;
            }

            const int first_template = *it;
            for (int x : existing_templates) {
                if (x != first_template) {
                    g.add_directed_edge(first_template, x);
                }
            }
        }

        std::vector<size_t> order;
        if (!g.top_sort_acyclic(&order)) {
            out << "NO" << std::endl;
            return;
        }

        out << "YES" << std::endl;
        for (int x : order) {
            out << x + 1 << " ";
        }
        out << std::endl;
	}


	ESopostavlenieShablonov() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
