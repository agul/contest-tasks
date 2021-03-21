#include "base/header.hpp"

class BDvoichnieUdaleniya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        std::string s;
        in >> s;
        int n = s.length();
        std::vector<int> a(n);
        for (int i : range(n)) {
            a[i] = s[i] - '0';
        }
        debug(a);
        auto dp = make_vector<int>(n + 1, 2, 2, -1);
        dp[0][0][0] = 0;

        auto valid = [&s](const int x, const int y) {
            return x < 0 || s[x] <= s[y];
        };

        for (int i : range(n)) {
            for (int last_value : range(2)) {
                for (int skipped : range(2)) {
                    if (dp[i][last_value][skipped] == -1) {
                        continue;
                    }
                    if (skipped == 1 && a[i] >= last_value) {
                        umax(dp[i + 1][a[i]][0], dp[i][last_value][1] + 1);
                    }
                    if (skipped == 0) {
                        umax(dp[i + 1][last_value][1], dp[i][last_value][0]);
                        if (a[i] >= last_value) {
                            umax(dp[i + 1][a[i]][0], dp[i][last_value][0] + 1);
                        }
                    }
                }
            }
        }
        const int max_len = std::max({dp[n][0][0], dp[n][0][1], dp[n][1][0], dp[n][1][1]});
        out << (max_len > 0 ? "YES" : "NO") << std::endl;
	}


	BDvoichnieUdaleniya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
