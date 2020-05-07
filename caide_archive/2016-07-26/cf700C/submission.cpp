#pragma comment(linker, "/STACK:66777216")
#pragma warning(disable : 4996)

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#pragma hdrstop

static constexpr long long LINF = 0x3f3f3f3f3f3f3f3fLL;

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

template<typename T>
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

#ifdef _MSC_VER

#endif

template<typename T, size_t N>
struct MakeVector {
	
};

template<typename T>
struct MakeVector<T, 1> {
	/// caide keep
	template<typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#define ll long long

#include <iterator>

template<typename T>
class IntegerIterator : public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T*, T> {
public:
	using value_type = T;

	constexpr explicit IntegerIterator(const value_type value) : value_(value) {}

	IntegerIterator& operator++() {
		++value_;
		return *this;
	}

	constexpr value_type operator*() const {
		return value_;
	}

	constexpr bool operator ==(const IntegerIterator rhs) const {
		return value_ == rhs.value_;
	}

	constexpr bool operator !=(const IntegerIterator rhs) const {
		return !(*this == rhs);
	}

private:
	value_type value_;

};

template<typename T>
class IntegerRange {
public:
	using const_iterator = IntegerIterator<T>;

	constexpr IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	constexpr const_iterator begin() const {
		return const_iterator(begin_);
	}

	constexpr const_iterator end() const {
		return const_iterator(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
constexpr IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

namespace Random {

	static std::chrono::system_clock::rep GetRandSeed() {
		return std::chrono::system_clock::now().time_since_epoch().count();
	}

}

class DSU {
public:
	DSU() : DSU(0) {}

	DSU(const size_t vertices_count) : parent_(vertices_count), sets_count_(vertices_count) {
		srand(static_cast<uint32_t>(Random::GetRandSeed()));
		std::iota(parent_.begin(), parent_.end(), 0);
	}

	void init(const size_t vertices_count) {
		srand(static_cast<uint32_t>(Random::GetRandSeed()));
		parent_.resize(vertices_count);
		std::iota(parent_.begin(), parent_.end(), 0);
		sets_count_ = vertices_count;
	}

	size_t find_set(const size_t vertex) {
		if (vertex != parent_[vertex]) {
			parent_[vertex] = find_set(parent_[vertex]);
		}
		return parent_[vertex];
	}

	bool unite(const size_t a, const size_t b) {
		size_t x = find_set(a);
		size_t y = find_set(b);
		if (x == y) {
			return false;
		}
		if ((rand() & 1) != 0) {
			std::swap(x, y);
		}
		parent_[x] = y;
		--sets_count_;
		return true;
	}

private:
	std::vector<size_t> parent_;
	size_t sets_count_;

};

enum GraphType {
	Weighted = 1
};

template<size_t MASK>
struct is_weighted 
{
	/// caide keep
	static constexpr bool value = (MASK & GraphType::Weighted) != 0;
};

template<typename T = long long, size_t MASK = 0>
class Graph {
public:
	using EdgesList = std::vector<size_t>;

	class Edge {
	public:
		constexpr explicit Edge(const std::vector<size_t>& from, const std::vector<size_t>& to,
			const std::vector<T>& weight, const size_t index) :
			from_(from), to_(to), weight_(weight), index_(index) {}

		size_t from() const {
			return from_[index_];
		}

		size_t to() const {
			return to_[index_];
		}

		constexpr size_t id() const {
			return index_;
		}

		void set_index(const size_t index) {
			index_ = index;
		}

	private:
		const std::vector<size_t>& from_;
		const std::vector<size_t>& to_;
		const std::vector<T>& weight_;
		size_t index_;

	};

	template<typename Range>
	class EdgesHolder {
	public:

		template<typename BaseConstIterator>
		class EdgeConstIterator : public BaseConstIterator {
		public:
			using value_type = Edge;
			
			using const_reference = const value_type&;

			constexpr explicit EdgeConstIterator(BaseConstIterator it, const std::vector<size_t>& from,
				const std::vector<size_t>& to, const std::vector<T>& weight) :
				BaseConstIterator(it), cur_edge_(from, to, weight, 0) {}

			const_reference operator*() {
				const typename BaseConstIterator::value_type index = this->BaseConstIterator::operator*();
				cur_edge_.set_index(index);
				return cur_edge_;
			}

		private:
			Edge cur_edge_;

		};

		using const_iterator = EdgeConstIterator<typename Range::const_iterator>;
		
		constexpr explicit EdgesHolder(const Range& range, const std::vector<size_t>& from,
			const std::vector<size_t>& to, const std::vector<T>& weight) :
			begin_(range.begin(), from, to, weight), end_(range.end(), from, to, weight) {}

		constexpr const_iterator begin() const {
			return begin_;
		}

		constexpr const_iterator end() const {
			return end_;
		}

	private:
		const const_iterator begin_;
		const const_iterator end_;

	};

	Graph(const size_t vertices_count) : vertices_count_(vertices_count), edges_(vertices_count) {}

	virtual ~Graph() {
		clear();
	}

	EdgesHolder<EdgesList> edges(const size_t vertex) const {
		return EdgesHolder<EdgesList>(edges_[vertex], from_, to_, weight_);
	}

	EdgesHolder<IntegerRange<size_t>> edges() const {
		return EdgesHolder<IntegerRange<size_t>>(range(from_.size()), from_, to_, weight_);
	}

	void clear();

	template<size_t Mask = MASK, typename std::enable_if<is_weighted<Mask>::value>::type* = nullptr>
	T weight(const size_t index) const {
		return weight_[index];
	}

	template<size_t Mask = MASK, typename std::enable_if<is_weighted<Mask>::value>::type* = nullptr>
	void add_directed_edge(const size_t from, const size_t to, const T weight) {
		weight_.emplace_back(weight);
		push_edge(from, to);
	}

protected:
	void push_edge(const size_t from, const size_t to) {
		const size_t edge_id = from_.size();
		from_.emplace_back(from);
		to_.emplace_back(to);
		edges_[from].emplace_back(edge_id);
	}

	std::vector<EdgesList> edges_;
	std::vector<size_t> from_;
	std::vector<size_t> to_;
	std::vector<T> weight_;

	size_t vertices_count_;

private:
	
};

template<typename T, size_t MASK>
void Graph<T, MASK>::clear() {
	vertices_count_ = 0;
	edges_.clear();
	from_.clear();
	to_.clear();
	weight_.clear();
}

template<typename T = long long, size_t MASK = 0>
class UndirectedGraph : public Graph<T, MASK> {
public:
	UndirectedGraph() : UndirectedGraph(0) {}
	UndirectedGraph(const size_t vertices_count) : Graph<T, MASK>(vertices_count) {}

	template<size_t Mask = MASK, typename std::enable_if<is_weighted<Mask>::value>::type* = nullptr>
	void add_bidirectional_edge(const size_t from, const size_t to, const T weight) {
		this->add_directed_edge(from, to, weight);
		this->add_directed_edge(to, from, weight);
	}

};

using namespace std;

using G = UndirectedGraph<ll, GraphType::Weighted>;

G graph;
vector<bool> alive, used;
vector<int> fup, tin;
int timer;

bool find_path(const int v, const int t, std::vector<int>& path) {
	if (v == t) {
		return true;
	}
	used[v] = true;
	for (const auto& it : graph.edges(v)) {
		const int to = it.to();
		const int id = it.id();
		if (!alive[id]) {
			continue;
		}
		path.emplace_back(id);
		if (!used[to] && find_path(to, t, path)) {
			return true;
		}
		path.pop_back();
	}
	return false;
}

void find_bridges(const int v, const int p, std::vector<int>& all_edges, std::unordered_set<int>& bridges) {
	used[v] = true;
	tin[v] = timer;
	fup[v] = timer;
	++timer;
	for (const auto& it : graph.edges(v)) {
		if (!alive[it.id()] || it.id() == (p ^ 1)) {
			continue;
		}
		all_edges.emplace_back(it.id());
		const size_t to = it.to();
		if (used[to]) {
			umin(fup[v], tin[to]);
		} else {
			find_bridges(to, it.id(), all_edges, bridges);
			umin(fup[v], fup[to]);
			if (fup[to] > tin[v]) {
				bridges.emplace(it.id());
			}
		}
	}
}

void solve(std::istream& in, std::ostream& out) {
	int n, m, s, t;
	in >> n >> m >> s >> t;
	graph = G(n);
	for (int i : range(m)) {
		int from, to, weight;
		in >> from >> to >> weight;
		--from, --to;
		graph.add_bidirectional_edge(from, to, weight);
	}
	--s, --t;
	vector<int> path, tmp_path;
	path.reserve(n);
	tmp_path.reserve(n);
	alive.assign(m * 2, true);
	used.assign(n, false);
	if (!find_path(s, t, path)) {
		out << 0 << endl << 0 << endl;
		return;
	}
	DSU dsu;
	ll ans = LINF;
	std::vector<int> edges, all_edges;
	std::unordered_set<int> bridges;
	for (const auto& id : path) {
		dsu.init(n);
		alive[id] = false;
		alive[id ^ 1] = false;
		for (const auto& it : graph.edges()) {
			if (!alive[it.id()]) {
				continue;
			}
			dsu.unite(it.from(), it.to());
		}
		if (dsu.find_set(s) != dsu.find_set(t)) {
			if (umin(ans, graph.weight(id))) {
				edges = { id };
			}
			alive[id] = true;
			alive[id ^ 1] = true;
			continue;
		}

		all_edges.clear();
		bridges.clear();
		fup.assign(n, -1);
		tin.assign(n, -1);
		timer = 0;
		used.assign(n, false);
		find_bridges(s, -1, all_edges, bridges);
		used.assign(n, false);
		tmp_path.clear();
		find_path(s, t, tmp_path);
		alive[id] = true;
		alive[id ^ 1] = true;

		for (const auto& it : tmp_path) {
			if (!bridges.count(it) && !bridges.count(it ^ 1)) {
				continue;
			}
			if (umin(ans, graph.weight(id) + graph.weight(it))) {
				edges = { id, it };
			}
		}
	}
	if (ans == LINF) {
		out << -1 << endl;
		return;
	}
	out << ans << endl;
	out << edges.size() << endl;
	for (const auto& it : edges) {
		out << it / 2 + 1 << " ";
	}
	out << endl;
}

#include <fstream>

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}

