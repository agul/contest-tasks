#include "base/header.hpp"
#include "maths/mod_int.hpp"

class DSozdateLi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	using Int = ModInt<int>;

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		out << dp[n] * 4 << std::endl;
	}

	const int kMaxn = 2222222;
	std::vector<Int> dp;
	std::vector<bool> colored;

	DSozdateLi() {
		dp.assign(kMaxn, 0);
		colored.assign(kMaxn, false);
		for (int i : range(3, kMaxn)) {
			dp[i] = (dp[i - 1] + dp[i - 2] * 2);
			if (!colored[i - 1] && !colored[i - 2]) {
				colored[i] = true;
				dp[i] += 1;
			}
		}
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
