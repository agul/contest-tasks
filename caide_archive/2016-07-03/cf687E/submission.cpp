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

constexpr const int INF = 0x3f3f3f3f;

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

template<typename T>
class Queue {
public:
	using value_type = T;
	using size_type = size_t;
	
	using const_reference = const value_type&;
	
	using container = std::vector<value_type>;

	Queue(const size_type max_size) : data_(container(max_size)) {
		clear();
	}

	Queue() = delete;

	Queue(const Queue&) = default;
	Queue& operator =(const Queue&) = default;
	Queue(Queue&&) = default;
	Queue& operator =(Queue&&) = default;

	constexpr bool empty() const {
		return head_index_ == tail_index_;
	}

	void clear() {
		head_index_ = 0;
		tail_index_ = 0;
	}

	void push(const_reference value) {
		data_[tail_index_++] = value;
	}

	value_type pop_front() {
		return data_[head_index_++];
	}

private:
	container data_;
	size_type head_index_;
	size_type tail_index_;

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

		constexpr Edge reversed() const {
			return Edge(to_, from_, weight_, index_);
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

	void init(const size_t vertices_count) {
		clear();
		vertices_count_ = vertices_count;
		edges_.resize(vertices_count_);
	}

	IntegerRange<size_t> vertices() const {
		return range(vertices_count_);
	}

	EdgesHolder<EdgesList> edges(const size_t vertex) const {
		return EdgesHolder<EdgesList>(edges_[vertex], from_, to_, weight_);
	}

	EdgesHolder<IntegerRange<size_t>> edges() const {
		return EdgesHolder<IntegerRange<size_t>>(range(from_.size()), from_, to_, weight_);
	}

	void clear();

	template<size_t Mask = MASK, typename std::enable_if<!is_weighted<Mask>::value>::type* = nullptr>
	void add_directed_edge(const size_t from, const size_t to) {
		push_edge(from, to);
	}

	template<size_t Mask = MASK, typename std::enable_if<!is_weighted<Mask>::value>::type* = nullptr>
	void add_directed_edge(const Edge& edge) {
		add_directed_edge(edge.from(), edge.to());
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
class DirectedGraph : public Graph<T, MASK> {
public:
	DirectedGraph() : DirectedGraph(0) {}
	DirectedGraph(const size_t vertices_count) : Graph<T, MASK>(vertices_count) {}

	void top_sort_rec(std::vector<size_t>* vertex_order) const;

	DirectedGraph reversed() const;
	
	size_t scc(std::vector<size_t>* vertex_color = nullptr) const;

private:
	void top_sort_rec_impl(const size_t vertex, std::vector<size_t>& order, std::vector<bool>& used) const;

};

template<typename T, size_t MASK>
DirectedGraph<T, MASK> DirectedGraph<T, MASK>::reversed() const {
	DirectedGraph<T, MASK> result;
	result.init(this->vertices_count_);
	for (const auto& edge : this->edges()) {
		result.add_directed_edge(edge.reversed());
	}
	return result;
}

template<typename T, size_t MASK>
void DirectedGraph<T, MASK>::top_sort_rec(std::vector<size_t>* vertex_order) const {
	std::vector<bool> used(this->vertices_count_, false);
	std::vector<size_t> order;
	for (const size_t v : this->vertices()) {
		if (!used[v]) {
			top_sort_rec_impl(v, order, used);
		}
	}
	std::reverse(order.begin(), order.end());
	vertex_order->swap(order);
}

template<typename T, size_t MASK>
void DirectedGraph<T, MASK>::top_sort_rec_impl(const size_t vertex, std::vector<size_t>& order, std::vector<bool>& used) const {
	used[vertex] = true;
	for (const auto& it : this->edges(vertex)) {
		const size_t to = it.to();
		if (!used[to]) {
			top_sort_rec_impl(to, order, used);
		}
	}
	order.emplace_back(vertex);
}

template<typename T, size_t MASK>
size_t DirectedGraph<T, MASK>::scc(std::vector<size_t>* vertex_color) const {
	const DirectedGraph<T, MASK> rev_graph = reversed();
	std::vector<size_t> order(this->vertices_count_);
	top_sort_rec(&order);
	std::vector<bool> used(this->vertices_count_, false);
	std::vector<size_t> color(this->vertices_count_);
	Queue<size_t> queue(this->vertices_count_);
	size_t components_count = 0;
	for (const auto& v : order) {
		if (!used[v]) {
			queue.clear();
			queue.push(v);
			while (!queue.empty()) {
				const size_t vertex = queue.pop_front();
				color[vertex] = components_count;
				used[vertex] = true;
				for (const auto& it : rev_graph.edges(vertex)) {
					const size_t to = it.to();
					if (!used[to]) {
						used[to] = true;
						queue.push(to);
					}
				}
			}
			++components_count;
		}
	}
	if (vertex_color != nullptr) {
		vertex_color->swap(color);
	}
	return components_count;
}

using namespace std;

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	DirectedGraph<int> graph(n);
	for (int i : range(m)) {
		int x, y;
		in >> x >> y;
		--x, --y;
		graph.add_directed_edge(x, y);
	}
	std::vector<size_t> color;
	const size_t components_count = graph.scc(&color);
	std::vector<size_t> cnt(components_count);
	for (const auto& it : color) {
		++cnt[it];
	}
	std::vector<size_t> min_loop(components_count, INF);
	Queue<size_t> q(n * 2);
	for (const auto& v : graph.vertices()) {
		const size_t component = color[v];
		if (cnt[component] == 1) {
			min_loop[component] = 0;
			continue;
		}
		q.clear();
		q.push(v);
		std::vector<size_t> dist(n, INF);
		while (!q.empty()) {
			const size_t vertex = q.pop_front();
			size_t len = dist[vertex];
			if (vertex == v && len == INF) {
				len = 0;
			}
			for (const auto& it : graph.edges(vertex)) {
				const size_t to = it.to();
				if (color[to] != component || !umin(dist[to], len + 1)) {
					continue;
				}
				q.push(to);
			}
		}
		umin(min_loop[component], dist[v]);
	}
	std::vector<std::pair<size_t, size_t>> vertices;
	for (size_t i = 0; i < n; ++i) {
		vertices.emplace_back(color[i], i);
	}
	sort(vertices.rbegin(), vertices.rend());
	for (const auto& it : vertices) {
		const size_t v = it.second;
		const size_t component = color[v];
		if (min_loop[component] == 0) {
			continue;
		}
		for (const auto& it : graph.edges(v)) {
			const size_t to = it.to();
			if (color[to] == component) {
				continue;
			}
			min_loop[component] = 0;
			break;
		}
	}
	const size_t loop_len = std::accumulate(min_loop.begin(), min_loop.end(), 0) * 998;
	const size_t loop_cnt = min_loop.size() - std::count(min_loop.begin(), min_loop.end(), 0);
	const size_t ans = loop_len + n + loop_cnt;
	out << ans << endl;
}

/* vvi graph;
bool used[MAXN];
int cnt[MAXN], ans;

const int MAGIC = 1000;

void dfs(int v) {
++cnt[v];
++ans;
if (cnt[v] < MAGIC) {
for (const auto& it : graph[v]) {
if (!used[it]) {
dfs(it);
}
break;
}
}
used[v] = true;
}

void solve(std::istream& in, std::ostream& out) {
int n, m;
in >> n >> m;
graph.clear();
graph.resize(n);
for (int i = 0; i < m; ++i) {
int x, y;
in >> x >> y;
--x, --y;
graph[x].emplace_back(y);
}
fill(used, 0);
fill(cnt, 0);
ans = 0;
for (int i = 0; i < n; ++i) {
if (!used[i]) {
dfs(i);
}
}
out << ans << endl;
} */

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

