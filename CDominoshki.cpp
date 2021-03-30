#include "base/header.hpp"

class CDominoshki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<int> cnt(3, 0);
        for (int i : range(n * m)) {
            std::string s;
            in >> s;
            cnt[std::count(all(s), '1')]++;
        }

        std::vector<std::vector<std::string>> ans(n, std::vector<std::string>(m));
        for (int i : range(n)) {
            for (int j : range(m)) {
                if (!ans[i][j].empty()) {
                    continue;
                }
                if (i < n - 1) {
                    if (cnt[1] > 1) {
                        ans[i][j] = "10";
                        ans[i + 1][j] = "01";
                        cnt[1] -= 2;
                        continue;
                    }
                    if (cnt[0] > 0 && cnt[2] > 0) {
                        ans[i][j] = "11";
                        ans[i + 1][j] = "00";
                        cnt[0] -= 1;
                        cnt[2] -= 1;
                        continue;
                    }
                }
                if (cnt[2] > 0) {
                    ans[i][j] = "11";
                    --cnt[2];
                }
                else if (cnt[1] > 0) {
                    ans[i][j] = "10";
                    --cnt[1];
                } else {
                    ans[i][j] = "00";
                    --cnt[0];
                }
            }
        }

        for (int i : range(n)) {
            for (int j : range(m)) {
                if (j > 0) {
                    out << " ";
                }
                out << ans[i][j];
            }
            out << std::endl;
        }
	}


	CDominoshki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
