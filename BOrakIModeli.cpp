#include "base/header.hpp"
#include "maths/maths.hpp"

class BOrakIModeli {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;
		auto dp = make_vector<int>(n, 1);
		for (int i : range(n)) {
			const int cur_value = i + 1;
			auto divs = divisors_vector(cur_value);
			for (const auto& div : divs) {
				if (div == cur_value) {
					continue;
				}
				if (a[i] > a[div - 1]) {
					umax(dp[i], dp[div - 1] + 1);
				}
			}
		}
		out << *max_element(dp) << std::endl;
	}


	BOrakIModeli() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
