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

#define vi std::vector<int>
#define vvi std::vector<vi>

const double EPS = 1e-9;

#ifdef _MSC_VER

#endif

namespace std {

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
	for (auto& it : vec) {
		in >> it;
	}
	return in;
}

template<typename T, typename U>
std::istream& operator>>(std::istream& in, std::pair<T, U>& rhs) {
	in >> rhs.first >> rhs.second;
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

	bool isBipartite(int w[], int cnt[], int v, int col) const {
		int * vertices = new int[vertexCount];
		vertices[0] = v;
		w[v] = col;
		int head = 0, tail = 1;
		while (head < tail) {
			int curVertex = vertices[head++], curColor = w[curVertex];
			if (cnt != NULL) {
				++cnt[curColor];
			}
			for (auto& it : edges[curVertex]) {
				int toVertex = to[it];
				if (w[toVertex] == -1) {
					w[toVertex] = curColor ^ 1;
					vertices[tail++] = toVertex;
				}
				else
					if (w[toVertex] != (curColor ^ 1)) {
						delete[] vertices;
						return false;
					}
			}
		}
		delete[] vertices;
		return true;
	}

	bool isBipartite(int w[], int cnt[] = NULL) const {
		std::fill_n(w, vertexCount, -1);
		if (cnt != NULL) {
			cnt[0] = cnt[1] = 0;
		}
		bool ret = true;
		for (int i = 0; i < vertexCount && ret; ++i) {
			if (w[i] == -1) {
				ret &= isBipartite(w, cnt, i, 0);
			}
		}
		return ret;
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

using namespace std;

const int MAXN = 1111;

UndirectedGraph graph(MAXN, MAXN * MAXN);

struct pt {
	int x, y;

	pt() : pt(0, 0) {}
	pt(int x, int y) : x(x), y(y) {}

	friend istream& operator >> (istream& in, pt& rhs) {
		in >> rhs.x >> rhs.y;
		return in;
	}

};

inline int det(int a, int b, int c, int d) {
	return a * d - b * c;
}

inline bool between(int a, int b, double c) {
	return min(a, b) <= c + EPS && c <= max(a, b) + EPS;
}

inline bool intersect_1(int a, int b, int c, int d) {
	if (a > b)  swap(a, b);
	if (c > d)  swap(c, d);
	return max(a, c) <= min(b, d);
}

bool intersect(pt a, pt b, pt c, pt d) {
	int A1 = a.y - b.y, B1 = b.x - a.x, C1 = -A1*a.x - B1*a.y;
	int A2 = c.y - d.y, B2 = d.x - c.x, C2 = -A2*c.x - B2*c.y;
	int zn = det(A1, B1, A2, B2);
	if (zn != 0) {
		double x = -det(C1, B1, C2, B2) * 1. / zn;
		double y = -det(A1, C1, A2, C2) * 1. / zn;
		return between(a.x, b.x, x) && between(a.y, b.y, y)
			&& between(c.x, d.x, x) && between(c.y, d.y, y);
	}
	else
		return det(A1, C1, A2, C2) == 0 && det(B1, C1, B2, C2) == 0
		&& intersect_1(a.x, b.x, c.x, d.x)
		&& intersect_1(a.y, b.y, c.y, d.y);
}

int used[MAXN];

void solve(istream& in, ostream& out) {
	int w, p, a, b, c;
	in >> w >> p;
	vector<pt> well(w);
	vector<std::pair<int, pt>> pipes(p);
	in >> well >> pipes;
	graph.clear();
	graph.initGraph(p);
	for (int i = 0; i < p; i++) {
		for (int j = i + 1; j < p; j++) {

			if (pipes[i].first == pipes[j].first) {
				continue;
			}

			if (!intersect(well[i], pipes[i].second, well[j], pipes[j].second)) {
				continue;
			}
			graph.addBidirectionalEdge(i, j);
		}
	}
	if (!graph.isBipartite(used)) {
		out << "im";
	}
	out << "possible" << endl;

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

