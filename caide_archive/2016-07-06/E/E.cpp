#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

struct Ans {
	int t = 0;
	int index = 0;
	int v = 0;
	int e = 0;
};

struct Edge {
	int a = 0;
	int b = 0;
	int p = 0;
};

bool cmp_edge(Edge a, Edge b) {
	return a.p < b.p;
}
bool cmp_1(Ans a, Ans b) {
	return a.t < b.t;
}
bool cmp_2(Ans a, Ans b) {
	return a.index < b.index;
}

void solve(std::istream& in, std::ostream& out) {
	int n, m, a, b, p, q;
	in >> n >> m;
	vector<int> v(n, 0);
	vector<Edge> e(m);
	for (int i = 0; i < m; i++) {
		in >> a >> b >> p;
		a--; b--;
		e[i].a = a;
		e[i].b = b;
		e[i].p = p;
		v[a]++; v[b]++;
	}
	int count[5] = { 0,0,0,0,0 };
	int edge = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] > 2) {
			count[3]++;
			edge += v[i];
		}
		else count[v[i]]++;
	}
	for (int i = 0; i < n; i++) {
		if (v[i] > 2)count[3]++;
		else count[v[i]]++;
	}
	sort(e.begin(), e.end(), cmp_edge);
	in >> q;
	vector<Ans> rec(q);
	for (int i = 0; i < q; i++) {
		in >> rec[i].t; rec[i].index = i;
	}
	sort(rec.begin(), rec.end(), cmp_1);
	int l = 0;
	for (int i = 0; i < q; i++) {
		while ((l < m) && (e[l].p < rec[i].t)) {
			if (v[e[l].a] <= 3) {
				count[v[e[l].a]]--;
				count[v[e[l].a] - 1]++;
			}
			else edge--;
			v[e[l].a]--;

			if (v[e[l].b] <= 3) {
				count[v[e[l].b]]--;
				count[v[e[l].b] - 1]++;
			}
			else edge--;
			v[e[l].b]--;
			l++;
		}
		int vv = 0, ee =0;
		vv = count[1] + count[3];
		ee = (count[1] + edge)/2;
		rec[i].e = ee;
		rec[i].v = vv;
		cout << rec[i].index << ' ' << rec[i].t << ' ' << rec[i].e << ' ' << rec[i].v << endl;
	}
	sort(rec.begin(), rec.end(), cmp_2);
	for (int i = 0; i < q; i++) {
		cout << rec[i].v << ' ' << rec[i].e << endl;
	}
}
