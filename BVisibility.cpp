#include "base/header.hpp"

class BVisibility {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m, x, y;
        in >> n >> m >> x >> y;
        std::vector<std::string> field(n);
        in >> field;

        --x, --y;
        int ans = 0;
        for (int dir : range(4)) {
            int curx = x, cury = y;
            while (curx >= 0 && cury >= 0 && curx < n && cury < m && field[curx][cury] == '.') {
                ++ans;
                curx += DX[dir];
                cury += DY[dir];
            }
        }
        ans -= 3;
        out << ans << std::endl;
	}


	BVisibility() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
