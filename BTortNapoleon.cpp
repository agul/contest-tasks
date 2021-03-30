#include "base/header.hpp"

class BTortNapoleon {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        std::vector<bool> ans(n, false);
        int last = n - 1;
        for (int i : downrange(n)) {
            if (last > i) {
                last = i;
            }
            int cur_cream = std::max(0, i - a[i] + 1);
            while (last >= cur_cream) {
                ans[last] = true;
                --last;
            }
        }

        for (bool x : ans) {
            out << (x ? 1 : 0) << " ";
        }
        out << std::endl;
	}


	BTortNapoleon() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
