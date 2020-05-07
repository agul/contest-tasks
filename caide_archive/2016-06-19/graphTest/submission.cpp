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

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

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

#define pii std::pair<int, int>

#include <iterator>

template<typename T>
class IntegerIterator : public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T*, T> {
public:
	using value_type = T;

	explicit IntegerIterator(const value_type value) : value_(value) {}

	IntegerIterator& operator++() {
		++value_;
		return *this;
	}

	value_type operator*() const {
		return value_;
	}

	bool operator ==(IntegerIterator rhs) const {
		return value_ == rhs.value_;
	}

	bool operator !=(IntegerIterator rhs) const {
		return !(*this == rhs);
	}

private:
	value_type value_;

};

template<typename T>
class IntegerRange {
public:
	using const_iterator = IntegerIterator<T>;

	IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	const_iterator begin() const {
		return const_iterator(begin_);
	}

	const_iterator end() const {
		return const_iterator(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

template<typename R>
void sort(R& range) {
	std::sort(range.begin(), range.end());
}

namespace Random {

	static std::chrono::system_clock::rep GetRandSeed() {
		return std::chrono::system_clock::now().time_since_epoch().count();
	}

}

class DSU {
public:
	DSU() = default;

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
		if (rand() & 1) {
			std::swap(x, y);
		}
		parent_[x] = y;
		--sets_count_;
		return true;
	}

	size_t sets_count() const {
		return sets_count_;
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

	Graph() = default;

	virtual ~Graph() {
		clear();
	}

	void init(const size_t vertices_count) {
		clear();
		vertices_count_ = vertices_count;
		edges_.resize(vertices_count_);
	}

	IntegerRange<size_t> vertices() const {
		return range(vertices_count_);
	}

	EdgesHolder<IntegerRange<size_t>> edges() const {
		return EdgesHolder<IntegerRange<size_t>>(range(from_.size()), from_, to_, weight_);
	}

	void clear();

	size_t edges_count() const {
		return from_.size();
	}

	size_t from(const size_t index) const {
		return from_[index];
	}

	size_t to(const size_t index) const {
		return to_[index];
	}

	template<size_t Mask = MASK, typename std::enable_if<is_weighted<Mask>::value>::type* = nullptr>
	T weight(const size_t index) const {
		return weight_[index];
	}

	template<size_t Mask = MASK, typename std::enable_if<is_weighted<Mask>::value>::type* = nullptr>
	void add_directed_edge(const size_t from, const size_t to, const T weight) {
		weight_.emplace_back(weight);
		push_edge(from, to);
	}

	template<size_t Mask = MASK, typename std::enable_if<is_weighted<Mask>::value>::type* = nullptr>
	T minimal_spanning_tree(std::vector<size_t>* mst = nullptr) const {
		std::vector<size_t> graph_edges(edges_count());
		std::iota(graph_edges.begin(), graph_edges.end(), 0);
		std::sort(graph_edges.begin(), graph_edges.end(), [&](const size_t& lhs, const size_t& rhs) {
			return weight(lhs) < weight(rhs);
		});
		DSU dsu;
		dsu.init(vertices_count_);
		T total_weight = 0;
		std::vector<size_t> tree;
		for (const auto& it : graph_edges) {
			if (dsu.unite(from(it), to(it))) {
				total_weight += weight(it);
				tree.emplace_back(it);
			}
		}
		if (mst != nullptr) {
			mst->swap(tree);
		}
		return total_weight;
	}

	bool is_connected() const;

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

template<typename T, size_t MASK>
bool Graph<T, MASK>::is_connected() const {
	DSU dsu;
	dsu.init(vertices_count_);
	for (const auto& it : edges()) {
		dsu.unite(it.from(), it.to());
	}
	return dsu.sets_count() == 1;
}

template<typename T = long long, size_t MASK = 0>
class UndirectedGraph : public Graph<T, MASK> {
public:
	UndirectedGraph() = default;

};

using namespace std;

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	UndirectedGraph<ll, GraphType::Weighted> graph;
	graph.init(n);
	for (int i : range(m)) {
		int from, to;
		ll weight;
		in >> from >> to >> weight;
		graph.add_directed_edge(from, to, weight);
	}
	if (!graph.is_connected()) {
		out << "NON-CONNECTED" << endl;
		return;
	}
	std::vector<size_t> mst;
	const ll ans = graph.minimal_spanning_tree(&mst);
	out << ans << endl;
	std::vector<std::vector<pii>> res(n);
	for (const auto& it : mst) {
		res[graph.from(it)].emplace_back(graph.to(it), graph.weight(it));
		res[graph.to(it)].emplace_back(graph.from(it), graph.weight(it));
	}
	for (const size_t v : graph.vertices()) {
		out << v << " :";
		bool first = true;
		sort(res[v]);
		for (const auto& jt : res[v]) {
			if (first) {
				first = false;
			}
			else {
				out << ",";
			}
			out << " " << jt.first << "(" << jt.second << ")";
		}
		out << endl;
	}
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

