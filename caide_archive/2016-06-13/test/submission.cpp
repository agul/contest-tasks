#pragma comment(linker, "/STACK:66777216")

#include <cstdio>
#pragma warning(disable : 4996)
#include <algorithm>
#include <array>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <utility>
#include <functional>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <queue>
#include <cmath>
#include <random>
#include <sstream>
#include <numeric>
#include <limits>
#include <chrono>
#include <type_traits>
#pragma hdrstop

#ifdef _MSC_VER
#include <intrin.h>

#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#define fill(a, x) memset(a, x, sizeof(a))
#define sz(a) ((int)a.size())

#define ll int64_t

#define vi std::vector<int>
#define vvi std::vector<vi>

#ifdef _MSC_VER

#endif

class Graph {
public:
	enum Type {
		GT_WEIGHTED = 1,
		GT_FLOW = 2
	};

	int *from, *to, *parent;
	ll *weight;
	vvi edges;
	int maxVertexNum, maxEdgesNum;
	int vertexCount, edgesCount;

	Graph(const int maxVertexNum, const int maxEdgesNum, const int mask = 0) : maxVertexNum(maxVertexNum), maxEdgesNum(maxEdgesNum) {
		from = new int[maxEdgesNum];
		to = new int[maxEdgesNum];
		edges.resize(maxVertexNum);
		weight = (mask & GT_WEIGHTED ? new ll[maxEdgesNum] : NULL);
		vertexCount = 0;
		edgesCount = 0;
	}

	virtual ~Graph() {
		deepClear();
	}

	void clear(int size = -1) {
		edgesCount = 0;
		size = (size == -1 ? sz(edges) : std::min(size, sz(edges)));
		if (size == -1) {
			size = sz(edges);
		}
		for (int i = 0; i < size; ++i) {
			edges[i].clear();
		}
	}

	void deepClear() {
		maxVertexNum = 0;
		maxEdgesNum = 0;
		edgesCount = 0;
		edges.clear();
		if (from != NULL) {
			delete[] from;
		}
		if (to != NULL) {
			delete[] to;
		}
		if (weight != NULL) {
			delete[] weight;
		}
		if (parent != NULL) {
			delete[] parent;
		}
	}

	int addDirectedEdge(const int _from, const int _to) {
		from[edgesCount] = _from;
		to[edgesCount] = _to;
		edges[_from].emplace_back(edgesCount);
		return edgesCount++;
	}

private:
	
};

class UndirectedGraph : public Graph {
public:

	UndirectedGraph(const int maxVertexNum, const int maxEdgesNum, const int mask = 0) : Graph(maxVertexNum, maxEdgesNum << 1, mask) {}

	void initGraph(const int _vertexCount) {
		vertexCount = _vertexCount;
	}

	void addBidirectionalEdge(const int _from, const int _to) {
		addDirectedEdge(_from, _to);
		addDirectedEdge(_to, _from);
	}

private:
	
};

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
	IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	IntegerIterator<T> begin() const {
		return IntegerIterator<T>(begin_);
	}

	IntegerIterator<T> end() const {
		return IntegerIterator<T>(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

template<typename T>
IntegerRange<T> range(const T from, const T to) {
	return IntegerRange<T>(from, to);
}

using namespace std;

const int MAXN = 222222;

int deg[MAXN];
ll x, y, n, cnt;
UndirectedGraph graph(MAXN, MAXN);

bool is_sun() {
	for (int i : range(n)) {
		if (deg[i] == n - 1) {
			return true;
		}
	}
	return false;
}

int dfs(int v, int p) {
	int sum = 0;
	for (const auto& it : graph.edges[v]) {
		int to = graph.to[it];
		if (to != p) {
			sum += dfs(to, v);
		}
	}
	if (sum < 2) {
		return 1;
	}
	cnt += sum - 1;
	return 0;
}

void solve(istream& ins, ostream& out) {
	ins >> n >> x >> y;
	graph.clear();
	graph.initGraph(n);
	fill(deg, 0);
	for (int i : range(1LL, n)) {
		int from, to;
		ins >> from >> to;
		--from, --to;
		graph.addBidirectionalEdge(from, to);
		++deg[from];
		++deg[to];
	}
	if (n == 2) {
		out << x << endl;
		return;
	}
	if (is_sun()) {
		out << min(x + y * (n - 2), x * 2 + y * (n - 3)) << endl;
		return;
	}
	if (x >= y) {
		out << y * (n - 1) << endl;
		return;
	}
	cnt = 0;
	cnt += dfs(0, -1);
	out << x * (n - cnt) + y * (cnt - 1) << endl;
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

