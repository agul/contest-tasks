#include "base/header.hpp"

class Reversort {
public:
	static constexpr bool kWriteCaseNumber = true;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        std::set<int> values(all(a));
        int ans = 0;
        for (int i : range(n - 1)) {
            int index = i;
            while (a[index] > *values.begin()) {
                ++index;
            }
            values.erase(values.begin());
            ans += index - i + 1;
            std::reverse(a.begin() + i, a.begin() + index + 1);
        }
        out << ans << std::endl;
	}


	Reversort() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
