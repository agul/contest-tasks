#include "base/header.hpp"
#include "graph/dsu.hpp"

class EMedvezhonokIZabitoeDerevo2 {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	const int kMaxn = 5555;
	const int kThreshold = 100;

	void solve(std::istream& in, std::ostream& out) {
        int n, m, k;
        in >> n >> m >> k;
        std::vector<SafeUnorderedSet<int>> forbidden(n);
        DSU dsu(n);
        for (int i : range(m)) {
            int x, y;
            in >> x >> y;
            --x, --y;
            forbidden[x].emplace(y);
            forbidden[y].emplace(x);
        }

        auto free = [&forbidden](const int from, const int to) {
            return from != to && forbidden[from].count(to) == 0;
        };

        const int max_degree = n - 1 - forbidden.front().size();
        int min_degree = 0;
        for (int v : range(1, n)) {
            if (forbidden[v].size() == n - 2 && free(0, v)) {
                ++min_degree;
                dsu.unite(0, v);
            }
        }
        if (std::min(n - 1, min_degree + 1) > k || max_degree < k) {
            out << "impossible" << std::endl;
            return;
        }

        if (n <= kMaxn) {
            for (int from : range(1, n)) {
                for (int to : range(from + 1, n)) {
                    if (free(from, to)) {
                        dsu.unite(from, to);
                    }
                }
            }
            for (int to : range(1, n)) {
                if (free(0, to) && dsu.unite(0, to)) {
                    ++min_degree;
                }
            }
            if (dsu.sets_count() != 1 || min_degree > k) {
                out << "impossible" << std::endl;
                return;
            }
            out << "possible" << std::endl;
            return;
        }

        std::vector<pii> vertices(n);
        for (int v : range(n)) {
            vertices[v] = {n - 1 - forbidden[v].size(), v};
        }
        sort(vertices);

        std::vector<bool> valid_set;
        auto mark_valid = [&dsu, &valid_set, &n, &vertices, this]() {
            valid_set.assign(n, false);
            dsu.finalize();
            for (int i : range(kThreshold, n)) {
                valid_set[dsu.find_set(vertices[i].second)] = true;
            }
        };

        auto is_valid = [&dsu, &valid_set](const int v) {
            return valid_set[dsu.find_set(v)];
        };

        for (int i : range(kThreshold)) {
            const int v = vertices[i].second;
            if (v == 0) {
                continue;
            }
            for (int to : range(1, n)) {
                if (free(v, to)) {
                    dsu.unite(v, to);
                }
            }
        }

        mark_valid();
        for (int i : range(kThreshold)) {
            const int v = vertices[i].second;
            if (!is_valid(v) && free(0, v) && dsu.unite(0, v)) {
                ++min_degree;
            }
        }

        mark_valid();
        if (!is_valid(0)) {
            for (int v : range(1, n)) {
                if (is_valid(v) && free(0, v) && dsu.unite(0, v)) {
                    ++min_degree;
                    break;
                }
            }
        } else {
            ++min_degree;
        }

        mark_valid();
        const bool any_invalid = !std::all_of(range(n).begin(), range(n).end(), is_valid);
        if (any_invalid || min_degree > k) {
            out << "impossible" << std::endl;
            return;
        }

        out << "possible" << std::endl;
	}


	EMedvezhonokIZabitoeDerevo2() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
