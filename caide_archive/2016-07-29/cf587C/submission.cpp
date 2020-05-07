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

#define all(a) a.begin(), a.end()

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

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

	IntegerIterator& operator--() {
		--value_;
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
class ReversedIntegerRange {
public:
	using const_iterator = IntegerIterator<T>;
	using reverse_iterator = std::reverse_iterator<const_iterator>;

	constexpr ReversedIntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	constexpr reverse_iterator begin() const {
		return reverse_iterator(const_iterator(begin_));
	}

	constexpr reverse_iterator end() const {
		return reverse_iterator(const_iterator(end_));
	}

private:
	T begin_;
	T end_;

};

template<typename T>
constexpr IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

template<typename T>
constexpr ReversedIntegerRange<T> inclusiveDownrange(const T from) {
	return ReversedIntegerRange<T>(from + 1, 0);
}

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

	Graph(const size_t vertices_count) : vertices_count_(vertices_count), edges_(vertices_count) {}

	virtual ~Graph() {
		clear();
	}

	EdgesHolder<EdgesList> edges(const size_t vertex) const {
		return EdgesHolder<EdgesList>(edges_[vertex], from_, to_, weight_);
	}

	void clear();

	size_t vertices_count() const {
		return vertices_count_;
	}

	template<size_t Mask = MASK, typename std::enable_if<!is_weighted<Mask>::value>::type* = nullptr>
	void add_directed_edge(const size_t from, const size_t to) {
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

	template<size_t Mask = MASK, typename std::enable_if<!is_weighted<Mask>::value>::type* = nullptr>
	void add_bidirectional_edge(const size_t from, const size_t to) {
		this->add_directed_edge(from, to);
		this->add_directed_edge(to, from);
	}

};

using namespace std;

int __;

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

