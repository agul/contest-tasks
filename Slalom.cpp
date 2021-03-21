#include "base/header.hpp"

class Slalom {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        auto a = make_vector<int>(n, 0, 0);
        for (int i : range(n)) {
            a[i].assign(i + 1, -INF);
        }
        auto dp = a;
        // dp.emplace_back(std::vector<int>(n + 1, -INF));
        in >> a;

        dp[0][0] = a[0][0];
        for (int i : range(n - 1)) {
            for (int j : inclusiveRange(i)) {
                umax(dp[i + 1][j], dp[i][j] + a[i + 1][j]);
                umax(dp[i + 1][j + 1], dp[i][j] + a[i + 1][j + 1]);
            }
        }
        debug(dp);
        out << *max_element(dp[n - 1]) << std::endl;
	}


	Slalom() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
