#include "base/header.hpp"

class ATsepnayaReaktsiya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		auto a = std::vector<pii>(n);
		in >> a;

		sort(a);
		std::vector<int> ans(n, 0);
		for (int i : range(n)) {
			int x = a[i].X;
			int dist = a[i].Y;
			auto it = lower_bound(a, pii{x - dist, 0});
			if (it == a.begin()) {
				ans[i] = 1;
			} else {
				const int index = it - a.begin() - 1;
				debug(i, index, *it);
				ans[i] = ans[index] + 1;
			}
		}
		debug(ans);
		out << n - *max_element(ans) << std::endl;
	}


	ATsepnayaReaktsiya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {}

};
