#include "base/header.hpp"

class EGoroskop {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        std::string s;
        int right, wrong;
        in >> s >> right >> wrong;

        const int n = s.length();
        auto dp = make_vector<int>(n + 1, right + 1, wrong + 1, -INF);
        dp[0][0][0] = 0;
        int ans = 0;
        for (int i : inclusiveRange(n)) {
            for (int correct : inclusiveRange(right)) {
                for (int incorrect : inclusiveRange(wrong)) {
                    const int value = dp[i][correct][incorrect];
                    umax(ans, value);
                    if (i == n) {
                        continue;
                    }
                    if (value == -INF) {
                        continue;
                    }
                    if (s[i] == 'G') {
                        if (correct < right) {
                            umax(dp[i + 1][correct + 1][0], value + 1);
                        }
                        if (incorrect < wrong) {
                            umax(dp[i + 1][0][incorrect + 1], value);
                        }
                    } else {
                        if (correct < right) {
                            umax(dp[i + 1][correct + 1][0], value);
                        }
                        if (incorrect < wrong) {
                            umax(dp[i + 1][0][incorrect + 1], value + 1);
                        }
                    }
                }
            }
        }

        out << ans << std::endl;
	}


	EGoroskop() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
