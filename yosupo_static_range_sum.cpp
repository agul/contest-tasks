#include "base/header.hpp"
#include "data_structures/fenwick_tree.hpp"

class yosupo_static_range_sum {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, q;
		in >> n >> q;
		std::vector<ll> a(n);
		in >> a;

		FenwickTreeSum<ll> fenwick_tree(a);
		for (int i : range(q)) {
			int x, y;
			in >> x >> y;
			out << fenwick_tree.query(x, y - 1) << std::endl;
		}
	}


	yosupo_static_range_sum() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
