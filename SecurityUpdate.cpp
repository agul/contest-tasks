#include "base/header.hpp"
#include "graph/undirected_graph.hpp"
#include "collections/queue/queue.hpp"

class SecurityUpdate {
public:
	static constexpr bool kWriteCaseNumber = true;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		std::vector<pii> know_cnt;
		std::vector<pii> know_dist;
		UndirectedGraph<int> graph(n);
		for (int i : range(1, n)) {
			int x;
			in >> x;
			if (x < 0) {
				know_cnt.emplace_back(-x, i);
			} else {
				know_dist.emplace_back(x, i);
			}
		}
		for (int i : range(m)) {
			int from, to;
			in >> from >> to;
			graph.add_bidirectional_edge(from - 1, to - 1);
		}

		sort(know_cnt);
		sort(know_dist);
		std::vector<bool> added(n, false);
		std::vector<int> dist(n, INF);
		dist[0] = 0;
		std::vector<int> ans(m, -1);

		added[0] = true;

		int cnt_added = 1;
		int index_cnt = 0;
		int index_dist = 0;
		int min_dist = 0;
		while (cnt_added < n) {
			std::vector<bool> proposed(n, false);
			int proposed_cnt = 0;
			++min_dist;
			while (index_cnt < know_cnt.size() && know_cnt[index_cnt].first <= cnt_added) {
				proposed[know_cnt[index_cnt].second] = true;
				++proposed_cnt;
				++index_cnt;
			}
			if (index_dist < know_dist.size()) {
				if (proposed_cnt == 0) {
					min_dist = know_dist[index_dist].first;
				}
				while (index_dist < know_dist.size() && know_dist[index_dist].first == min_dist) {
					proposed[know_dist[index_dist].second] = true;
					++proposed_cnt;
					++index_dist;
				}
			}
			// debug(proposed_cnt, proposed);
			assert(proposed_cnt > 0);
			for (int v : range(n)) {
				if (!added[v]) {
					continue;
				}
				for (const auto& edge : graph.edges(v)) {
					const int to = edge.to();
					if (!proposed[to]) {
						continue;
					}
					const int id = edge.id() / 2;
					ans[id] = min_dist - dist[v];
					dist[to] = min_dist;
				}
			}
			for (int v : range(n)) {
				if (proposed[v]) {
					added[v] = true;
					++cnt_added;
				}
			}
			// debug(cnt_added, dist);
		}

		for (int& x : ans) {
			if (x == -1) {
				x = 1000000;
			}
		}

		for (int x : ans) {
			out << x << " ";
		}
		out << std::endl;
	}


	SecurityUpdate() {}


	static void calculate(const UndirectedGraph<int, GraphType::Weighted>& graph, std::vector<int>& dist, std::vector<int>& cnt) {
		const int n = graph.vertices_count();
		std::set<pii> q;
		q.emplace(0, 0);

		dist = std::vector<int>(n, INF);
		cnt = std::vector<int>(n, 0);
		std::vector<bool> visited(n, false);
		dist[0] = 0;
		while (!q.empty()) {
			const int v = q.begin()->second;
			q.erase(q.begin());
			if (visited[v]) {
				continue;
			}
			visited[v] = true;
			const int cur_len = dist[v];
			for (const auto& edge : graph.edges(v)) {
				const int to = edge.to();
				const int len = edge.weight();
				if (umin(dist[to], cur_len + len)) {
					q.emplace(dist[to], to);
				}
			}
		}

		for (int i : range(n)) {
			for (int j : range(n)) {
				if (dist[j] < dist[i]) {
					cnt[i]++;
				}
			}
		}
	}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;
		for (int _ : range(1, 1 + testsCount)) {
			std::string skip;
			out >> skip >> skip;

			int n, m;
			in >> n >> m;
			std::vector<int> expected_cnt(n, 0);
			std::vector<int> expected_dist(n, 0);
			for (int i : range(1, n)) {
				int x;
				in >> x;
				if (x < 0) {
					expected_cnt[i] = -x;
				} else {
					expected_dist[i] = x;
				}
			}
			std::vector<int> edges_len(m);
			out >> edges_len;
			if (*min_element(edges_len) < 1) {
				debug("FAIL incorrect length ", edges_len);
				return false;
			}
			UndirectedGraph<int, GraphType::Weighted> graph(n);
			for (int i : range(m)) {
				int from, to;
				in >> from >> to;
				graph.add_bidirectional_edge(from - 1, to - 1, edges_len[i]);
			}

			std::vector<int> dist(n, INF);
			std::vector<int> cnt(n);
			calculate(graph, dist, cnt);

			for (int i : range(n)) {
				if (expected_cnt[i] > 0 && cnt[i] != expected_cnt[i]) {
					debug("FAIL", _, i, expected_cnt[i], cnt[i]);
					return false;
				}
				if (expected_dist[i] > 0 && expected_dist[i] != dist[i]) {
					debug("FAIL", _, i, expected_dist[i], dist[i]);
					return false;
				}
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 50;
		const int kMaxValue = 10;
		const int kMaxm = 200;

		const int n = Random::get(2, kMaxn);
		const int m = Random::get(n - 1, std::min(kMaxm, n * (n - 1) / 2));

		auto g = jngen::Graph::random(n, m).connected().g().shuffled();
		auto weights = jngen::Array::random(m, 1, kMaxValue);
		g.setEdgeWeights(weights);

		auto graph_edges = g.edges();
		UndirectedGraph<int, GraphType::Weighted> graph(n);
		for (size_t i : range(m)) {
			const auto& edge = graph_edges[i];
			graph.add_bidirectional_edge(edge.first, edge.second, weights[i]);
		}

		std::vector<int> dist(n, INF);
		std::vector<int> cnt(n);
		calculate(graph, dist, cnt);

		test << 1 << std::endl;
		test << n << " " << m << std::endl;
		for (int i : range(1, n)) {
			const int info_type = Random::get(0, 1);
			if (info_type == 0) {
				test << -cnt[i] << " ";
			} else {
				test << dist[i] << " ";
			}
		}
		test << std::endl;
		for (const auto& it : graph_edges) {
			test << it.first + 1 << " " << it.second + 1 << std::endl;
		}

	}

};
