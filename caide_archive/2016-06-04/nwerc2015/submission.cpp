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

#define sz(a) ((int)a.size())

#define ll int64_t

#define pii std::pair<int, int>

#define vi std::vector<int>
#define vvi std::vector<vi>

template<class T> 
inline bool umax(T& a, const T& b) {
	return (a < b ? a = b, true : false);
}

namespace std {

template<typename T, typename U>
struct hash<std::pair<T, U>> {
	std::size_t operator()(const std::pair<T, U>& lhs) const {
		return lhs.first * 877117 + lhs.second;
	}
};

#ifdef _MSC_VER

#endif

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
	for (auto& it : vec) {
		in >> it;
	}
	return in;
}

}

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

	void initGraph(const int _vertexCount) {
		vertexCount = _vertexCount;
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

	bool topSortAcyclic(int order[]) const
		// non-recursive topological sorting, works only for acyclic graphs 
	{
		int * degree = new int[vertexCount];
		std::fill_n(degree, vertexCount, 0);
		for (int i = 0; i < edgesCount; ++i) {
			++degree[to[i]];
		}
		int head = 0, tail = 0;
		for (int i = 0; i < vertexCount; ++i) {
			if (!degree[i]) {
				order[tail++] = i;
			}
		}
		while (head < tail) {
			int curVertex = order[head++];
			for (auto& it : edges[curVertex]) {
				int toVertex = to[it];
				if (!(--degree[toVertex])) {
					order[tail++] = toVertex;
				}
			}
		}
		delete[] degree;
		return tail == vertexCount;
	}

	void topSortRec(int order[]) const {
		bool * used = new bool[vertexCount];
		std::fill_n(used, vertexCount, false);
		int cnt = 0;
		for (int i = 0; i < vertexCount; ++i) {
			if (!used[i]) {
				_topSortDfs(i, order, used, cnt);
			}
		}
		std::reverse(order, order + vertexCount);
	}

private:
	
	void _topSortDfs(const int v, int order[], bool used[], int& cnt) const
		// internal function for recursive topological sorting
	{
		used[v] = true;
		for (auto& it : edges[v]) {
			int toVertex = to[it];
			if (!used[toVertex]) {
				_topSortDfs(toVertex, order, used, cnt);
			}
		}
		order[cnt++] = v;
	}

};

int stronglyConnectedComponents(const Graph& g, const Graph& gr, int color[])
// g - graph, gr - reversed graph, color - output (index of SCC for each vertex)
{
	int n = g.vertexCount;
	int * order = new int[n];
	bool * used = new bool[n];
	int * q = new int[n];
	std::fill_n(order, n, 0);
	g.topSortRec(order);
	int cnt = 0;
	std::fill_n(used, n, false);
	for (int i = 0; i < n; ++i) {
		int v = order[i];
		if (!used[v]) {
			int head = 0, tail = 1;
			q[0] = v;
			while (head < tail) {
				int curVertex = q[head++];
				color[curVertex] = cnt;
				used[curVertex] = true;
				for (auto& it : gr.edges[curVertex]) {
					int to = gr.to[it];
					if (!used[to]) {
						used[to] = true;
						q[tail++] = to;
					}
				}
			}
			++cnt;
		}
	}
	delete[] q;
	delete[] used;
	delete[] order;
	return cnt;
}

using namespace std;

const int MAXN = 222222;

int color[MAXN], order[MAXN];
Graph graph(MAXN, MAXN * 3), rev(MAXN, MAXN * 3), tree(MAXN, MAXN * 3);
std::unordered_set<pii> edges;

void add(int x, int y) {
	if (edges.count({ x, y })) {
		return;
	}
	edges.insert({ x, y });
	--x;
	--y;
	graph.addDirectedEdge(x, y);
	rev.addDirectedEdge(y, x);
}

void add_tree(int x, int y) {
	if (edges.count({ x, y })) {
		return;
	}
	edges.insert({ x, y });
	tree.addDirectedEdge(x, y);
}

void solve(istream& in, ostream& out) {
	int n;
	in >> n;
	vector<int> a(n), b(n), c(n);
	in >> a >> b >> c;
	edges.clear();
	graph.clear();
	tree.clear();
	rev.clear();
	graph.initGraph(n);
	rev.initGraph(n);
	for (int i = 1; i < n; ++i) {
		add(a[i - 1], a[i]);
		add(b[i - 1], b[i]);
		add(c[i - 1], c[i]);
	}
	stronglyConnectedComponents(graph, rev, color);
	edges.clear();
	std::vector<int> vcnt(n, 0);
	int max_color = 0;
	for (int vertex = 0; vertex < n; ++vertex) {

		const int cur_col = color[vertex];
		umax(max_color, cur_col + 1);
		++vcnt[cur_col];
	}
	tree.initGraph(max_color);
	for (const auto& vertex : graph.edges) {
		for (const auto& it : vertex) {
			int to = graph.to[it];
			int from = graph.from[it];
			if (color[to] != color[from]) {
				add_tree(color[from], color[to]);
			}
		}
	}
	tree.topSortAcyclic(order);
	vector<ll> cnt(max_color, 0);
	ll ans = 0;
	for (int i = max_color - 1; i >= 0; --i) {
		int v = order[i];
		for (const auto& it : tree.edges[v]) {
			int to = tree.to[it];
			cnt[v] += cnt[to];
		}
		ans += cnt[v] * vcnt[v];
		cnt[v] += vcnt[v];
	}
	out << ans << endl;
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

