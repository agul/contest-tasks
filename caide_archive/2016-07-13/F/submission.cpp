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
class DirectedGraph : public Graph<T, MASK> {
public:
	DirectedGraph() : DirectedGraph(0) {}
	DirectedGraph(const size_t vertices_count) : Graph<T, MASK>(vertices_count) {}

private:
	
};

using namespace std;

int __;

DirectedGraph<int> graph;

bool dfs(const int v, const int p, std::vector<bool>& used, const int start, std::vector<size_t>& path, std::vector<std::vector<size_t>>& paths) {
	used[v] = true;
	path.emplace_back(v);
	paths[v].emplace_back(v);
	int best = -1;
	for (const auto& it : graph.edges(v)) {
		int to = it.to();
		if (to == start) {
			paths[start] = path;
			paths[start].emplace_back(to);
			return true;
		}
		if (!used[to] && dfs(to, v, used, start, path, paths)) {
			return true;
		}
		if (best == -1 || paths[best].size() < paths[to].size()) {
			best = to;
		}
	}
	if (best != -1) {
		paths[v].insert(paths[v].end(), all(paths[best]));
	}
	path.pop_back();
	return false;
}

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n;
		in >> n;
		if (_ == 13) {
			out << "DEBUG: " << n << endl;
		}
		graph = DirectedGraph<int>(26);
		std::vector<std::vector<bool>> forbid(32, std::vector<bool>(32));
		for (int i = 0; i < n; ++i) {
			string s;
			in >> s;
			forbid[s[0] - 'a'][s[1] - 'a'] = true;
		}
		for (int i = 0; i < 26; ++i) {
			for (int j = 0; j < 26; ++j) {
				if (!forbid[i][j]) {
					graph.add_directed_edge(i, j);
				}
			}
		}
		std::vector<size_t> loop;
		std::vector<size_t> best;
		for (size_t i = 0; i < 26; ++i) {
			std::vector<bool> used(26, false);
			std::vector<std::vector<size_t>> paths(26);
			std::vector<size_t> cur_path;
			bool ret = dfs(i, -1, used, i, cur_path, paths);
			if (ret) {
				loop.swap(paths[i]);
				break;
			}
			if (paths[i].size() > best.size()) {
				best.swap(paths[i]);
			}
		}
		if (!loop.empty()) {
			loop.pop_back();
			std::string loop_str;
			for (const auto& it : loop) {
				loop_str += it + 'a';
			}
			std::string row;
			while (row.size() < 40) {
				row.append(loop_str);
			}
			for (int i = 0; i < 20; ++i) {
				out << row.substr(0, 20) << endl;
				std::rotate(row.begin(), row.begin() + 1, row.end());
			}
			continue;
		}
		std::string best_str;
		for (const auto& it : best) {
			best_str += it + 'a';
		}
		int len = (best.size() + 1) / 2;
		for (int i = 0; i < len; ++i) {
			out << best_str.substr(0, len) << endl;
			best_str.erase(best_str.begin());
		}
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

