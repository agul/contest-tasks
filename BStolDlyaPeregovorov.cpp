#include "base/header.hpp"

class BStolDlyaPeregovorov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<std::string> field(n);
        in >> field;

        auto pref = make_vector<int>(n + 1, m + 1, 0);
        for (int i : range(1, n + 1)) {
            for (int j : range(1, m + 1)) {
                pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + (field[i - 1][j - 1] == '0' ? 0 : 1);
            }
        }

        int ans = 0;
        for (int i : range(1, n + 1)) {
            for (int j : range(1, m + 1)) {
                for (int x : range(i, n + 1)) {
                    for (int y : range(j, m + 1)) {
                        if (pref[x][y] - pref[i - 1][y] - pref[x][j - 1] + pref[i - 1][j - 1] == 0) {
                            umax(ans, (x - i + 1 + y - j + 1) * 2);
                        }
                    }
                }
            }
        }
        out << ans << std::endl;
	}


	BStolDlyaPeregovorov() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
