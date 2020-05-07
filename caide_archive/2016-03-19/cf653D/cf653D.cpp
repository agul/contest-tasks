#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

template <typename FlowSize>
class DinicFlow {
	struct Edge {
		std::size_t from, to;
		FlowSize cap;
		FlowSize flow;
	};
public:
	DinicFlow(std::size_t n) : g(n), queue(n), pointer(n), used(n), d(n) {
	}

	void addEdge(std::size_t from, std::size_t to, FlowSize capacity) {
		return addTwoSidedEdge(from, to, capacity, 0);
	}

	void addTwoSidedEdge(std::size_t from, std::size_t to, FlowSize capacity, FlowSize backwardCapacity) {
		Edge edge = { from, to, capacity, 0 };
		g[from].push_back(edges.size());
		edges.push_back(edge);

		Edge backwardEdge = { to, from, backwardCapacity, 0 };
		g[to].push_back(edges.size());
		edges.push_back(backwardEdge);
	}

	Edge getEdge(std::size_t id) {
		return edges[id];
	}

	FlowSize findFlow(std::size_t from, std::size_t to, FlowSize infinity = std::numeric_limits<FlowSize>::max()) {
		FlowSize flow = 0;
		while (bfs(from, to)) {
			memset(&pointer[0], 0, sizeof(std::size_t) * pointer.size());
			while (FlowSize pushed = dfs(from, to, infinity)) {
				flow += pushed;
			}
		}
		return flow;
	}

	std::size_t edgesCount() const {
		return edges.size();
	}

private:

	bool bfs(std::size_t from, std::size_t to) {
		memset(&used[0], false, sizeof(char) * used.size());
		std::size_t qh = 0, qt = 0;
		queue[qt++] = from;
		used[from] = true;
		while (qh != qt) {
			std::size_t v = queue[qh++];
			for (std::size_t id : g[v]) {
				Edge& edge = edges[id];
				if (used[edge.to]) {
					continue;
				}
				if (edge.cap == edge.flow) {
					continue;
				}
				used[edge.to] = true;
				d[edge.to] = d[v] + 1;
				queue[qt++] = edge.to;
			}
		}
		return used[to];
	}

	FlowSize dfs(std::size_t v, std::size_t to, FlowSize mx) {
		if (mx == 0) {
			return 0;
		}

		if (v == to) {
			return mx;
		}

		for (std::size_t& i = pointer[v]; i < g[v].size(); ++i) {
			std::size_t id = g[v][i];
			Edge& e = edges[id];
			if (d[e.to] == d[v] + 1) {
				if (FlowSize pushed = dfs(e.to, to, std::min(mx, e.cap - e.flow))) {
					e.flow += pushed;
					edges[id ^ 1].flow -= pushed;
					return pushed;
				}
			}
		}
		return 0;
	}

	std::vector<std::vector<std::size_t>> g;
	std::vector<Edge> edges;

	/**
	* Variables for actual flow calculation.
	* TODO: consider moving them so that they are not stored when not needed
	*/
	std::vector<std::size_t> queue; //std::queue is to slow, not removing values is faster
	std::vector<std::size_t> pointer;
	std::vector<char> used;
	std::vector<FlowSize> d;
};

struct Edge {
	int from, to, cap;
	Edge() {}
	void read() {
		io >> from >> to >> cap;
		--from, --to;
	}
};

void solve(istream& ins, ostream& out) {
	int n, m, x;
	io >> n >> m >> x;
	vector<Edge> e(m);
	for (int i = 0; i < m; ++i) {
		e[i].read();
	}
	double L = 0, R = 1e6;
	for (int iter = 0; iter < 60; ++iter) {
		double md = (L + R) / 2;
		if (md < EPS) {
			break;
		}
		DinicFlow<ll> flow(n);
		for (int i = 0; i < m; ++i) {
			ll cap = static_cast<ll>(e[i].cap / md + EPS);
			flow.addEdge(e[i].from, e[i].to, cap);
		}
		ll flow_value = flow.findFlow(0, n - 1);
		(flow_value < x ? R : L) = md;
	}
	out << fixed << setprecision(16) << L * x << endl;
}
