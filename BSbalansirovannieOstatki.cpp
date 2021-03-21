#include "base/header.hpp"

class BSbalansirovannieOstatki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        std::vector<int> c(3, 0);
        in >> n;
        for (int i : range(n)) {
            int x;
            in >> x;
            ++c[x % 3];
        }
        n /= 3;

        int ans = 0;
        while (*max_element(c) > n) {
            const int max_index = max_element(c) - c.begin();
            const int cur = c[max_index] - n;
            ans += cur;
            c[(max_index + 1) % 3] += cur;
            c[max_index] -= cur;
        }
        out << ans << std::endl;
	}


	BSbalansirovannieOstatki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
