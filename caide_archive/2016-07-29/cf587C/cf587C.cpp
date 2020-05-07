#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

using InfoSet = std::vector<int>;

UndirectedGraph<int> graph;
vector<InfoSet> values;

inline void normalize(InfoSet& cur, const int max_cnt = 10) {
	if (cur.size() > max_cnt) {
		cur.erase(cur.begin() + max_cnt, cur.end());
	}
}

inline void combine(InfoSet& cur, const InfoSet& rhs, const int max_cnt = 10) {
	std::vector<int> tmp(cur.size() + rhs.size());
	std::merge(all(cur), all(rhs), tmp.begin());
	cur.swap(tmp);
	normalize(cur, max_cnt);
}

class Precalc {
public:
	template<typename T, size_t MASK>
	Precalc(const UndirectedGraph<T, MASK>& graph) : up_(graph.vertices_count()), precalc_(graph.vertices_count()), tin_(graph.vertices_count()),
		tout_(graph.vertices_count()), timer_(0) {
		log_ = 1;
		while ((1 << log_) <= graph.vertices_count()) {
			++log_;
		}
		for (auto& it : up_) {
			it.resize(log_ + 1);
		}
		for (auto& it : precalc_) {
			it.resize(log_ + 1);
		}
		dfs(graph, 0, 0);
	}

	const std::vector<size_t> tin() const {
		return tin_;
	}

	const std::vector<size_t> tout() const {
		return tout_;
	}

	bool upper(const size_t lhs, const size_t rhs) const {
		const size_t time_in = tin_[rhs];
		return tin_[lhs] <= time_in && tout_[lhs] >= time_in;
	}
	
	InfoSet build_path(const size_t p, const size_t v, const size_t max_cnt) const {
		if (p == v) {
			return{};
		}
		InfoSet ans;
		size_t vertex = v;
		for (const size_t i : inclusiveDownrange(log_)) {
			if (!upper(up_[vertex][i], p)) {
				const size_t parent = up_[vertex][i];
				combine(ans, precalc_[vertex][i], max_cnt);
				vertex = parent;
			}
		}
		combine(ans, precalc_[vertex][0], max_cnt);
		return ans;
	}

	InfoSet query(const size_t lhs, const size_t rhs, const size_t max_cnt) const {
		if (upper(lhs, rhs)) {
			InfoSet path = build_path(lhs, rhs, max_cnt);
			combine(path, values[lhs], max_cnt);
			return path;
		}
		if (upper(rhs, lhs)) {
			InfoSet path = build_path(rhs, lhs, max_cnt);
			combine(path, values[rhs], max_cnt);
			return path;
		}
		size_t vertex = lhs;
		InfoSet ans;
		for (const size_t i : inclusiveDownrange(log_)) {
			if (!upper(up_[vertex][i], rhs)) {
				vertex = up_[vertex][i];
			}
		}
		const size_t lca = up_[vertex][0];
		InfoSet path_a = build_path(lca, lhs, max_cnt);
		InfoSet path_b = build_path(lca, rhs, max_cnt);
		combine(path_a, path_b, max_cnt);
		combine(path_a, values[lca], max_cnt);
		return path_a;
	}

private:
	template<typename T, size_t MASK>
	void dfs(const UndirectedGraph<T, MASK>& graph, const size_t vertex, const size_t parent) {
		tin_[vertex] = timer_++;
		up_[vertex][0] = parent;
		normalize(values[vertex]);
		precalc_[vertex][0] = values[vertex];
		for (size_t i = 1; i <= log_; ++i) {
			const size_t parent = up_[vertex][i - 1];
			up_[vertex][i] = up_[parent][i - 1];
			precalc_[vertex][i] = precalc_[parent][i - 1];
			combine(precalc_[vertex][i], precalc_[vertex][i - 1]);
		}
		for (const auto& it : graph.edges(vertex)) {
			const size_t to = it.to();
			if (to == parent) {
				continue;
			}
			dfs(graph, to, vertex);
		}
		tout_[vertex] = timer_++;
	}

	std::vector<std::vector<InfoSet>> precalc_;
	std::vector<std::vector<size_t>> up_;
	std::vector<size_t> tin_;
	std::vector<size_t> tout_;
	size_t log_;
	size_t timer_;
};

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m >> __;
	graph = UndirectedGraph<int>(n);
	for (int i : range(n - 1)) {
		int from, to;
		in >> from >> to;
		--from, --to;
		graph.add_bidirectional_edge(from, to);
	}
	values.assign(n, {});
	for (int i : range(m)) {
		int city;
		in >> city;
		--city;
		values[city].emplace_back(i);
	}
	Precalc precalc(graph);
	for (int _ : range(__)) {
		int u, v, max_cnt;
		in >> u >> v >> max_cnt;
		--u, --v;
		const InfoSet path = precalc.query(u, v, max_cnt);
		out << path.size() << " ";
		for (const auto& it : path) {
			out << it + 1 << " ";
		}
		out << endl;
	}
}
