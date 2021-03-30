#include "base/header.hpp"

class FTreugolniePuti {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;

        /*
        auto dp = make_vector<int>(n + 1, n + 1, INF);
        dp[0][0] = 0;
        for (int i : range(n)) {
            for (int j : inclusiveRange(i)) {
                int delta = (i + j) % 2;
                delta ^= 1;
                umin(dp[i + 1][j + delta], dp[i][j]);
                umin(dp[i + 1][j + (delta ^ 1)], dp[i][j] + 1);
            }
        }

        for (int i : range(n + 1)) {
            for (int j : range(i + 1)) {
                out << dp[i][j] << " ";
            }
            out << std::endl;
        }
        return;
        */

        std::vector<pii> points(n);
        for (auto& pt : points) {
            in >> pt.first;
            --pt.first;
        }
        for (auto& pt : points) {
            in >> pt.second;
            --pt.second;
        }
        sort(points);

        ll ans = 0;

        debug(points);
        int x = 0;
        int y = 0;
        for (const auto& pt : points) {
            debug(ans);
            int diff_x = pt.first - x;
            int diff_y = pt.second - y;
            debug(x, y, pt, diff_x, diff_y);

            const int odd = ((x + y) % 2 == 1);
            std::tie(x, y) = pt;
            if (!odd) {
                if (diff_x == diff_y) {
                    ans += diff_x;
                    continue;
                }
                const int diff = diff_x - diff_y - 1;
                ans += (diff + 1) / 2;
                continue;
            } else {
                const int diff = diff_x - diff_y;
                ans += (diff + 1) / 2;
                continue;
            }
        }

        out << ans << std::endl;
	}


	FTreugolniePuti() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
