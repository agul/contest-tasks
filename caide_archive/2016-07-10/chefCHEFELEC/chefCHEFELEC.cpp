#include "base/header.hpp"
#include "graph/dsu.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

struct Edge {
	int from, to, weight;

	Edge() : Edge(0, 0, 0) {}
	Edge(const int from, const int to, const int weight) : from(from), to(to), weight(weight) {}

	bool operator < (const Edge& rhs) const {
		return weight < rhs.weight;
	}
};

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	for (int _ : range(__)) {
		int n;
		string s;
		in >> n >> s;
		vector<int> a(n);
		in >> a;
		DSU dsu(n + 1);
		std::vector<Edge> edges;
		for (int i : range(n)) {
			if (s[i] == '1') {
				dsu.unite(0, i + 1);
			}
			if (i > 0) {
				edges.emplace_back(i, i + 1, a[i] - a[i - 1]);
			}
		}
		sort(edges);
		ll ans = 0;
		for (const auto& it : edges) {
			if (dsu.unite(it.from, it.to)) {
				ans += it.weight;
			}
		}
		out << ans << endl;
	}
}
