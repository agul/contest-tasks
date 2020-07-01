#include "base/header.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/lca.hpp"
#include "collections/queue/queue.hpp"

class DPosledneeSledstvieYekhaba {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m, k;
		in >> n >> m >> k;
		const int minimum_independent_set_size = (k + 1) / 2;
		UndirectedGraph<int, GraphType::Weighted> graph(n);
		for (int i : range(m)) {
			int from, to;
			in >> from >> to;
			graph.add_bidirectional_edge(from - 1, to - 1, 1);
		}

		std::vector<size_t> mst;
		graph.minimal_spanning_tree(&mst);

		UndirectedGraph<int> tree(n);
		for (size_t edge_id : mst) {
			tree.add_bidirectional_edge(graph.from(edge_id), graph.to(edge_id));
		}

		std::vector<int> dist(n, -1);
		std::function<void(int, int, int)> dfs = [&tree, &dist, &dfs](const int v, const int p, const int cur_dist) {
			dist[v] = cur_dist;
			for (const auto& edge : tree.edges(v)) {
				const int to = edge.to();
				if (to == p) {
					continue;
				}
				dfs(to, v, cur_dist + 1);
			}
		};
		dfs(0, -1, 0);

		LCA lca(tree);
		auto find_distance = [&lca, &dist](const int from, const int to) {
			const int parent = lca.query(from, to);
			return dist[from] - dist[parent] + dist[to] - dist[parent];
		};

//		auto get_from_to_by_id = [&graph](const size_t edge_id) {
//			int from = graph.from(edge_id);
//			int to = graph.to(edge_id);
//			if (to < from) {
//				std::swap(from, to);
//			}
//			return pii{from, to};
//		};

		int min_length = INF;
		int add_edge = -1;
		std::unordered_set<size_t> tree_edges(all(mst));
		for (const auto& edge : graph.edges()) {
			const int id = edge.id();
			if (tree_edges.count(id) > 0 || tree_edges.count(id ^ 1) > 0) {
				continue;
			}
			const int from = edge.from();
			const int to = edge.to();

			const int cur_loop_distance = find_distance(from, to) + 1;
			if (cur_loop_distance < min_length) {
				min_length = cur_loop_distance;
				add_edge = id;
			}
		}

		if (add_edge == -1) {
			std::vector<int> odd;
			std::vector<int> even;
			for (int i : range(n)) {
				if (dist[i] % 2 == 0) {
					even.emplace_back(i);
				} else {
					odd.emplace_back(i);
				}
			}

			const auto& vec = (even.size() >= minimum_independent_set_size ? even : odd);
			out << 1 << std::endl;
			for (int i : range(minimum_independent_set_size)) {
				out << vec[i] + 1 << " ";
			}
			out << std::endl;
			return;
		}

		const int loop_start = graph.from(add_edge);
		tree.add_bidirectional_edge(loop_start, graph.to(add_edge));

		debug(min_length, loop_start);

		Queue<int> q(n);
		std::vector<int> loop_dist(n, INF);
		std::vector<int> prev(n, -1);

		auto add = [&q, &loop_dist, &prev](const int v, const int pv, const int dist) {
			if (loop_dist[v] > dist) {
				loop_dist[v] = dist;
				prev[v] = pv;
				q.push(v);
			}
		};

		std::vector<int> vertices;
		add(loop_start, -1, 0);
		while (!q.empty() && vertices.empty()) {
			const int v = q.pop_front();
			const int pv = prev[v];
			const int cur_dist = loop_dist[v];
			for (const auto& edge : tree.edges(v)) {
				const int to = edge.to();
				if (to == pv) {
					continue;
				}
				if (loop_dist[to] < INF) {
					int curv = v;
					while (curv != loop_start) {
						vertices.emplace_back(curv);
						curv = prev[curv];
					}
					vertices.emplace_back(loop_start);

					const int loop_half_size = vertices.size();

					curv = to;
					while (curv != loop_start) {
						vertices.emplace_back(curv);
						curv = prev[curv];
					}
					std::reverse(vertices.begin() + loop_half_size, vertices.end());
					break;
				}
				add(to, v, cur_dist + 1);
			}
		}
		if (vertices.size() <= k) {
			out << 2 << std::endl;
			out << vertices.size() << std::endl;
			for (int x : vertices) {
				out << x + 1 << " ";
			}
			out << std::endl;
			return;
		}
		out << 1 << std::endl;
		for (int i : range(minimum_independent_set_size)) {
			out << vertices[i * 2] + 1 << " ";
		}
		out << std::endl;
	}


	DPosledneeSledstvieYekhaba() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
