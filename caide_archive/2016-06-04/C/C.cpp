#include "Head.h"
#include "Graph/graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
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
