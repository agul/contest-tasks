#include "Head.h"
#include "maths.hpp"

using namespace std;

int __;
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

template<typename T>
class Point2D {
public:

	Point2D() : Point2D(0, 0) {}
	Point2D(const T x, const T y) : x_(x), y_(y) {}

	T sqr_dist(const Point2D& rhs) const {
		return sqr(x_ - rhs.x_) + sqr(y_ - rhs.y_);
	}

	double dist(const Point2D& rhs) const {
		return sqrt(sqr_dist(rhs));
	}

	friend istream& operator >>(istream& in, Point2D& point) {
		in >> point.x_ >> point.y_;
		return in;
	}

private:
	T x_;
	T y_;

};

class Pile {
public:
	Pile() : used(false), reachable(false) {}

	friend istream& operator >>(istream& in, Pile& pile) {
		in >> pile.pos >> pile.leaves;
		return in;
	}

	Point2D<int> pos;
	size_t leaves;
	bool used;
	bool reachable;

};

class Weaver {
public:
	Weaver() = default;

	friend istream& operator >>(istream& in, Weaver& rhs) {
		in >> rhs.pos >> rhs.leaves >> rhs.radius;
		rhs.radius = sqr(rhs.radius);
		return in;
	}

	bool reach(const Pile& pile) const {
		return pos.sqr_dist(pile.pos) <= radius;
	}

	Point2D<int> pos;
	size_t leaves;
	size_t radius;

};

void fail_output(ostream& out) {
	out << "Lonesome Willy" << endl;
}

void ok_output(ostream& out) {
	out << "Suiting Success" << endl;
}


void solve(istream& in, ostream& out) {
	in >> __;
	for (int _ = 0; _ < __; ++_) {
		int n, m;
		in >> n >> m;
		Weaver willy;
		vector<Weaver> weavers(n - 1);
		vector<Pile> piles(m);
		in >> willy >> weavers >> piles;
		for (auto& pile : piles) {
			if (willy.reach(pile)) {
				willy.leaves += pile.leaves;
				pile.used = true;
			}
		}
		bool ok = true;
		for (const auto& weaver : weavers) {
			ok &= (weaver.leaves <= willy.leaves);
			for (auto& pile : piles) {
				pile.reachable |= weaver.reach(pile);
			}
		}
		if (!ok) {
			fail_output(out);
			continue;
		}
		DinicFlow<int> flow(1 + piles.size() + weavers.size() + 1);
		int total = 0;
		for (int i = 0; i < piles.size(); ++i) {
			if (!piles[i].reachable || piles[i].used) {
				continue;
			}
			flow.addEdge(0, i + 1, piles[i].leaves);
			total += piles[i].leaves;
		}
		const int offset = 1 + piles.size();
		const int finish = piles.size() + weavers.size() + 1;
		for (int i = 0; i < weavers.size(); ++i) {
			flow.addEdge(i + offset, finish, willy.leaves - weavers[i].leaves);
		}
		for (int i = 0; i < piles.size(); ++i) {
			if (!piles[i].reachable || piles[i].used) {
				continue;
			}
			for (int j = 0; j < weavers.size(); ++j) {
				if (weavers[j].reach(piles[i])) {
					flow.addEdge(i + 1, j + offset, INF);
				}
			}
		}
		const int value = flow.findFlow(0, finish);
		if (value < total) {
			fail_output(out);
			continue;
		}
		ok_output(out);
	}
}
