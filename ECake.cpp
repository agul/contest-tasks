#include "base/header.hpp"
#include "maths/maths.hpp"

class ECake {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int x1, y1, x2, y2, x3, y3;
        in >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        const int d = gcd(std::abs(x3 - x2), std::abs(y3 - y2));
        debug(d, std::abs(x3 - x2), std::abs(y3 - y2));

        int ans = (std::abs(x3 - x1) + 1) + (std::abs(y2 - y1) + 1) + (d + 1) - 3;
        out << ans << std::endl;
	}


	ECake() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
