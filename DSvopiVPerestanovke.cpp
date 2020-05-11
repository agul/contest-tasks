#include "base/header.hpp"
#include "graph/dsu.hpp"

class DSvopiVPerestanovke {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		auto a = make_vector<int>(n, 0);
		in >> a;
		DSU dsu(n);
		for (int i : range(m)) {
			int x, y;
			in >> x >> y;
			--x, --y;
			dsu.unite(x, y);
		}
		dsu.finalize();
		const auto& parent = dsu.data();
		std::vector<std::set<int, std::greater<int>>> sets(n);
		for (int i : range(n)) {
			sets[parent[i]].emplace(a[i]);
		}
		for (int i : range(n)) {
			auto& cur_set = sets[parent[i]];
			const int x = *cur_set.begin();
			cur_set.erase(x);
			out << x << " ";
		}
		out << std::endl;
	}


	DSvopiVPerestanovke() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {}

};
