#include "base/header.hpp"
#include "graph/undirected_graph.hpp"
#include "collections/queue/queue.hpp"

class ADzhonniIVklad {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		UndirectedGraph<int> graph(n);
		for (int i : range(m)) {
			int from, to;
			in >> from >> to;
			--from, --to;
			graph.add_bidirectional_edge(from, to);
		}
		std::vector<pii> a;
		a.reserve(n);
		for (int i : range(n)) {
			int x;
			in >> x;
			a.emplace_back(x, i);
		}
		sort(a);

		Queue<int> q(n);
		int index = 0;
		int position = 0;
		std::vector<int> ans(n, -1);
		std::vector<int> color(n, -1);
		for (int topic : inclusiveRange(1, n)) {
			while (index < a.size() && a[index].first == topic) {
				q.push(a[index].second);
				++index;
			}
			while (!q.empty()) {
				const int v = q.pop_front();
				std::vector<int> neighbours;
				neighbours.reserve(graph.edges(v).size());
				for (const auto& edge : graph.edges(v)) {
					const int to = edge.to();
					if (color[to] == -1) {
						continue;
					}
					neighbours.emplace_back(color[to]);
				}
				sort(neighbours);
				int mex = 1;
				for (int x : neighbours) {
					if (x == mex) {
						++mex;
					} else
					if (mex < x) {
						break;
					}
				}
				if (mex != topic) {
					out << -1 << std::endl;
					debug(v, mex, topic);
					return;
				}
				ans[position] = v;
				++position;
				color[v] = topic;
			}
		}
		for (int x : ans) {
			out << x + 1 << " ";
		}
		out << std::endl;
	}


	ADzhonniIVklad() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
