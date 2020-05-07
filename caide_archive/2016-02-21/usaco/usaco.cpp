#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 2048;

struct Item {
	int len;
	int x, y;
	Item() {}

	

	void set(int _len, int _x, int _y) {
		len = _len;
		x = _x;
		y = _y;
	}

	bool operator < (const Item& rhs) const {
		return len < rhs.len;
	}
};

int a[MAXN], b[MAXN], p[MAXN * MAXN];
Item edges[MAXN * MAXN * 2];
ll ans;

int findSet(const int v) {
	if (v == p[v]) {
		return v;
	}
	return p[v] = findSet(p[v]);
}

void unite(int a, int b, int len) {
	a = findSet(a), b = findSet(b);
	if (a == b) {
		return;
	}
	if (rand() & 1) {
		std::swap(a, b);
	}
	ans += len;
	p[a] = b;
}

void solve(istream& ins, ostream& out) {
	srand(time(NULL));
	IO::assign_files("fencedin");
	int n, m, A, B;
	io >> A >> B >> n >> m;
	for (int i = 0; i < n; ++i) {
		io >> a[i];
	}
	for (int i = 0; i < m; ++i) {
		io >> b[i];
	}
	a[n] = 0;
	b[m] = 0;
	a[n + 1] = A;
	b[m + 1] = B;
	sort(a, a + n + 2);
	sort(b, b + m + 2);
	int cnt = 0;
	int cur_id = 0;
	for (int j = 1; j <= m + 1; ++j) {
		for (int i = 1; i <= n; ++i, ++cur_id) {
			edges[cnt++].set(b[j] - b[j - 1], cur_id, cur_id + 1);
		}
		++cur_id;
	}
	cur_id = 0;
	for (int j = 1; j <= m; ++j) {
		for (int i = 1; i <= n + 1; ++i, ++cur_id) {
			edges[cnt++].set(a[i] - a[i - 1], cur_id, cur_id + n +1);
		}
	}
	sort(edges, edges + cnt);
	const int V = (n + 1) * (m + 1);
	for (int i = 0; i < V; ++i) {
		p[i] = i;
	}
	ans = 0;
	for (int i = 0; i < cnt; ++i) {
		auto& edge = edges[i];
		unite(edge.x, edge.y, edge.len);
	}
	io << ans << endl;
}
