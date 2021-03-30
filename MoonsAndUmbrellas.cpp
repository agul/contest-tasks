#include "base/header.hpp"

class MoonsAndUmbrellas {
public:
	static constexpr bool kWriteCaseNumber = true;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        std::vector<int> cost(2);
        std::string s;
        in >> cost >> s;

        const int n = s.length();
        auto dp = make_vector<int>(n + 1, 2, INF);
        dp[0][0] = 0;
        dp[0][1] = 0;
        for (int i : range(n)) {
            if (s[i] == 'C') {
                dp[i + 1][0] = std::min(dp[i][0], dp[i][1] + cost[1]);
            }
            else if (s[i] == 'J') {
                dp[i + 1][1] = std::min(dp[i][1], dp[i][0] + cost[0]);
            } else {
                for (int ch : range(2)) {
                    dp[i + 1][ch] = std::min(dp[i][ch], dp[i][ch ^ 1] + cost[ch ^ 1]);
                }
            }
        }
        out << *min_element(dp[n]) << std::endl;
	}


	MoonsAndUmbrellas() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
