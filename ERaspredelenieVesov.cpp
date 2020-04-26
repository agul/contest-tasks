#include "base/header.hpp"
#include "graph/undirected_graph.hpp"
#include "queue.hpp"

class ERaspredelenieVesov {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			size_t n, m, a, b, c;
			in >> n >> m >> a >> b >> c;
			--a, --b, --c;
			auto weights = make_vector<ll>(m, 0);
			in >> weights;
			sort(weights);

			std::vector<ll> pref(m + 1, 0);
			for (int i : range(m)) {
				pref[i + 1] = pref[i] + weights[i];
			}

			graph.init(n);
			for (int i : range(m)) {
				int from, to;
				in >> from >> to;
				--from, --to;
				graph.add_bidirectional_edge(from, to, 1);
			}

			std::vector<ll> dist_a;
			std::vector<ll> dist_b;
			std::vector<ll> dist_c;

			graph.dijkstra(a, &dist_a);
			graph.dijkstra(b, &dist_b);
			graph.dijkstra(c, &dist_c);

			ll ans = LINF;
			debug(a, b, c);
			for (int i : range(n)) {
				const ll db = dist_b[i];
				const ll da = dist_a[i];
				const ll dc = dist_c[i];
				if (da + db + dc > m) {
					continue;
				}
				const ll cur = pref[db] + pref[da + db + dc];
				debug(i, cur, da, db, dc);
				umin(ans, cur);
			}
			out << ans << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	UndirectedGraph<ll, GraphType::Weighted> graph;
	size_t test_id_ = 0;
};
