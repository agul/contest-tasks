#include "base/header.hpp"

class DGazonokosilka {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<std::string> field(n);
        in >> field;

        std::vector<int> row_min(n + 1, INF), row_max(n + 1, -INF);
        int last_row = -1;
        for (int i : range(n)) {
            for (int j : range(m)) {
                if (field[i][j] == 'W') {
                    umin(row_min[i], j);
                    umax(row_max[i], j);
                    last_row = i;
                }
            }
        }

        n = last_row + 1;
        if (n == 0) {
            out << 0 << std::endl;
            return;
        }
        auto dp = make_vector<int>(n + 1, m + 1, 2, INF);
        dp[0][0][0] = 0;
        for (int row : range(n)) {
            for (int col : range(m)) {
                if (col + 1 < m) {
                    umin(dp[row][col + 1][0], dp[row][col][0] + 1);
                }
                if (row_max[row] <= col && row_max[row + 1] <= col) {
                    umin(dp[row + 1][col][1], dp[row][col][0] + 1);
                }
            }
            for (int col : downrange(m)) {
                if (col > 0) {
                    umin(dp[row][col - 1][1], dp[row][col][1] + 1);
                }
                if (row_min[row] >= col && row_min[row + 1] >= col) {
                    umin(dp[row + 1][col][0], dp[row][col][1] + 1);
                }
            }
        }
        int ans = INF;
        for (int col : range(m)) {
            for (int dir : range(2)) {
                umin(ans, dp[n][col][dir]);
            }
        }
        out << ans - 1 << std::endl;
	}


	DGazonokosilka() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
