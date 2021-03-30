#include "base/header.hpp"

class BMagicheskiiMassiv {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        ll ans = 0;
        int index = 0;
        while (index < n) {
            const int start = index;
            while (index < n && a[start] == a[index]) {
                ++index;
            }
            const ll len = index - start;
            ans += len * (len + 1) / 2;
        }
        out << ans << std::endl;
	}


	BMagicheskiiMassiv() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
