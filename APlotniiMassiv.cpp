#include "base/header.hpp"

class APlotniiMassiv {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        int ans = 0;
        for (int i : range(n - 1)) {
            int x = std::min(a[i], a[i + 1]);
            const int y = std::max(a[i], a[i + 1]);
            while (x * 2 < y) {
                ++ans;
                x *= 2;
            }
        }
        out << ans << std::endl;
	}


	APlotniiMassiv() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
