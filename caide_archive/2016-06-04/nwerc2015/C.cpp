#include "Head.h"
#include "Graph/graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 222222;

class Point {
	int x;
	int y;
	int s;
	Point(int xx=0,int yy=0,int ss=0) {
		x = xx;
		y = yy;
		s = ss;
	}
};

void solve(istream& in, ostream& out) {
	ll w, p,a,b,c;
	in >> w >> p;
	vector<int> istok_x(w), istok_y(w);
	for (int i = 0; i < w; i++) {
		cin >> istok_x[i] >> istok_y[i];
	}
	vector<Point> pies(p);
	for (int i = 0; i < p; i++) {
		cin >> a >> b >> c;
		pies[i]=
	}

}
