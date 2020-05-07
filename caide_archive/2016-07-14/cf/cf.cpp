#include "base/header.hpp"
#include "graph/dsu.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	vector<int> a(n);
	in >> a;
	DSU dsu(n);
	for (int i : range(m)) {
		int x, y;
		in >> x >> y;
		--x, --y;
		dsu.unite(x, y);
	}
	dsu.finalize();
	std::unordered_map<int, std::vector<int>> vals;
	for (int i : range(n)) {
		const int x = dsu.find_set(i);
		vals[x].emplace_back(i);
	}
	for (auto& it : vals) {
		sort(it.second);
	}
	std::vector<int> ans(n);
	for (int i : range(n)) {
		const int x = dsu.find_set(i);
		auto& vec = vals[x];
		ans[i] = vec.back() + 1;
		vec.pop_back();
	}

	for (const auto& it : ans) {
		out << it << " ";
	}
	out << endl;
}
