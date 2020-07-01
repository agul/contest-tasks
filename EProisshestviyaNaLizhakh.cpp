#include "base/header.hpp"
#include "graph/directed_graph.hpp"
#include "collections/queue/queue.hpp"

#ifdef HOME
// #include <jngen/jngen.h>
#endif

class EProisshestviyaNaLizhakh {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		DirectedGraph<int> graph(n);
		for (int i : range(m)) {
			int x, y;
			in >> x >> y;
			graph.add_directed_edge(x - 1, y - 1);
		}
		std::vector<size_t> order;
		graph.top_sort_acyclic(&order);



		auto reversed = graph.reversed();
		std::vector<bool> deleted(n, false);
		std::vector<int> dist(n, 0);

		for (int v : order) {
			for (const auto& edge : reversed.edges(v)) {
				const int to = edge.to();
				if (deleted[to]) {
					continue;
				}
				umax(dist[v], dist[to] + 1);
			}
			if (dist[v] >= 2) {
				deleted[v] = true;
			}
		}
//
//
//
//		Queue<int> q(n);
//		std::vector<bool> used(n, false);
//
//		for (int v : range(n)) {
//			if (!used[v]) {
//				q.push(v);
//				dist[v] = 0;
//			}
//			while (!q.empty()) {
//				const int v = q.pop_front();
//				if (deleted[v]) {
//					continue;
//				}
//				const int cur_dist = dist[v];
//
//			}
//		}

		std::vector<int> ans;
		for (int i : range(n)) {
			if (deleted[i]) {
				ans.emplace_back(i);
			}
		}

		out << ans.size() << std::endl;
		for (int x : ans) {
			out << x + 1 << " ";
		}
		out << std::endl;
	}


	EProisshestviyaNaLizhakh() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;
		for (int testid : inclusiveRange(1, testsCount)) {
			int n, m;
			in >> n >> m;
			DirectedGraph<int> graph(n);
			for (int i : range(m)) {
				int x, y;
				in >> x >> y;
				graph.add_directed_edge(x - 1, y - 1);
			}

			std::vector<bool> deleted(n, false);
			int deleted_count;
			out >> deleted_count;

			const int max_deleted_count = 4 * n / 7;
			if (deleted_count > max_deleted_count) {
				debug("FAIL too many deleted vertices:", deleted_count, max_deleted_count);
				return false;
			}

			for (int i : range(deleted_count)) {
				int x;
				out >> x;
				deleted[x - 1] = true;
			}

			bool ok = true;
			std::function<void(int, int)> dfs = [&graph, &deleted, &ok, &dfs](const int v, const int dist) {
				if (dist >= 2) {
					ok = false;
					return;
				}
				for (const auto& edge : graph.edges(v)) {
					const int to = edge.to();
					if (deleted[to]) {
						continue;
					}
					dfs(to, dist + 1);
				}
			};

			for (int v : range(n)) {
				if (!deleted[v]) {
					dfs(v, 0);
				}
			}

			if (!ok) {
				debug("FAIL");
				return false;
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
#ifdef HOME
		const int kMaxn = 1000;
		const int kMaxm = kMaxn * 100;

		const int n = Random::get(1, kMaxn);
		const int m = Random::get(1, kMaxm);
		auto g = jngen::Graph::random(n, m).directed().allowMulti().acyclic().g();

		std::vector<int> cnt(n, 0);
		std::vector<pii> edges;
		for (const auto& it : g.edges()) {
			const int from = it.first;
			const int to = it.second;
			if (cnt[from]++ >= 2) {
				continue;
			}
			edges.emplace_back(from, to);
		}
		test << 1 << std::endl;
		test << n << " " << edges.size() << std::endl;
		for (const auto& it : edges) {
			test << it.first + 1 << " " << it.second + 1 << std::endl;
		}
#endif
	}

};
