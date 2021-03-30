#include "base/header.hpp"

class ReversortEngineering {
public:
	static constexpr bool kWriteCaseNumber = true;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, cost;
        in >> n >> cost;
        std::vector<int> a(n);
        std::iota(all(a), 1);

        auto dp = make_vector<bool>(n + 1, cost + 1, false);
        auto last = make_vector<int>(n + 1, cost + 1, -1);
        dp[0][0] = true;
        for (int i : range(n - 1)) {
            for (int j : range(cost)) {
                if (!dp[i][j]) {
                    continue;
                }
                for (int delta : inclusiveRange(1, n - i)) {
                    if (j + delta > cost) {
                        break;
                    }
                    dp[i + 1][j + delta] = true;
                    last[i + 1][j + delta] = delta;
                }
            }
        }

        if (!dp[n - 1][cost]) {
            out << "IMPOSSIBLE" << std::endl;
            return;
        }

        int cur_pos = cost;
        for (int i : inclusiveDownrange(n - 1, 1)) {
            const int delta = last[i][cur_pos];
            std::reverse(a.begin() + i - 1, a.begin() + i - 1 + delta);
            cur_pos -= delta;
        }
        for (int x : a) {
            out << x << " ";
        }
        out << std::endl;
	}


	ReversortEngineering() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
