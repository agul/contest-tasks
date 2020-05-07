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

#define fill(a, x) memset(a, x, sizeof(a))

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

template<typename R>
void reverse(R& range) {
	std::reverse(range.begin(), range.end());
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

		size_t from() const {
			return from_[index_];
		}

		size_t to() const {
			return to_[index_];
		}

		template<size_t Mask = MASK, typename std::enable_if<is_weighted<Mask>::value>::type* = nullptr>
		T weight() const {
			return weight_[index_];
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

	EdgesHolder<EdgesList> edges(const size_t vertex) const {
		return EdgesHolder<EdgesList>(edges_[vertex], from_, to_, weight_);
	}

	EdgesHolder<IntegerRange<size_t>> edges() const {
		return EdgesHolder<IntegerRange<size_t>>(range(from_.size()), from_, to_, weight_);
	}

	void clear();

	template<size_t Mask = MASK, typename std::enable_if<is_weighted<Mask>::value>::type* = nullptr>
	void add_directed_edge(const size_t from, const size_t to, const T weight) {
		weight_.emplace_back(weight);
		push_edge(from, to);
	}

	template<size_t Mask = MASK, typename std::enable_if<is_weighted<Mask>::value>::type* = nullptr>
	void add_directed_edge(const Edge& edge) {
		add_directed_edge(edge.from(), edge.to(), edge.weight());
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

	DirectedGraph reversed() const;
	
private:
	
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

using namespace std;

const int MAXN = 5010;

struct Node {
	ll len;
	int vertex;
	int cnt;

	Node(const ll len, const int vertex, const int cnt) : len(len), vertex(vertex), cnt(cnt) {}

	bool operator < (const Node& rhs) const {
		return len > rhs.len;
	}
};

ll dist[MAXN][MAXN];
bool used[MAXN][MAXN];
priority_queue<Node> q;

void add(const ll len, const int v, const int cnt) {
	q.emplace(len, v, cnt);
}

void solve(std::istream& in, std::ostream& out) {
	int n, m, t;
	in >> n >> m >> t;
	DirectedGraph<ll, GraphType::Weighted> graph(n);
	for (int i : range(m)) {
		int from, to;
		ll weight;
		in >> from >> to >> weight;
		--from, --to;
		graph.add_directed_edge(from, to, weight);
	}
	fill(used, false);
	fill(dist, LINF);
	dist[0][1] = 0;
	add(0, 0, 1);
	while (!q.empty()) {
		auto it = q.top();
		q.pop();
		const int v = it.vertex;
		const int cnt = it.cnt;
		if (it.len > dist[v][cnt]) {
			continue;
		}
		for (const auto& edge : graph.edges(v)) {
			const int to = edge.to();
			const ll new_len = it.len + edge.weight();
			if (umin(dist[to][cnt + 1], new_len)) {
				add(new_len, to, cnt + 1);
			}
		}
	}
	int ans = 0;
	for (int i : range(n)) {
		if (dist[n - 1][i] <= t) {
			ans = i;
		}
	}
	vector<int> res;
	int cur_index = n - 1;
	int cur_cnt = ans;
	auto gr = graph.reversed();
	do {
		res.emplace_back(cur_index);
		const ll cur_dist = dist[cur_index][cur_cnt];
		for (const auto& it : gr.edges(cur_index)) {
			const int to = it.to();
			const ll len = it.weight();
			if (dist[to][cur_cnt - 1] + len == cur_dist) {
				cur_index = to;
				--cur_cnt;
				break;
			}
		}
	} while (cur_index != 0);
	res.emplace_back(0);
	reverse(res);
	out << ans << endl;
	for (const auto& it : res) {
		out << it + 1 << " ";
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

