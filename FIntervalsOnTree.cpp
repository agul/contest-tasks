#include "base/header.hpp"
#include "graph/undirected_graph.hpp"
#include "graph/dsu.hpp"

class FIntervalsOnTree {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		auto count = [n](const int from, const int to) {
			return static_cast<ll>(from) * (n - to + 1);
		};

		ll ans = 0;
		for (int i : inclusiveRange(1, n)) {
			ans += count(i, i);
		}

		UndirectedGraph<> tree(n);
		for (int i : range(n - 1)) {
			int from, to;
			in >> from >> to;
			if (from > to) {
				std::swap(from, to);
			}
			ans -= count(from, to);
		}

		out << ans << std::endl;
	}


	FIntervalsOnTree() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
