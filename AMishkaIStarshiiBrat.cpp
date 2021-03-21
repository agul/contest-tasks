#include "base/header.hpp"

class AMishkaIStarshiiBrat {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        ll a, b;
        in >> a >> b;
        for (int i : range(50)) {
            if (a > b) {
                out << i << std::endl;
                return;
            }
            a *= 3;
            b *= 2;
        }
        out << "WTF" << std::endl;
	}


	AMishkaIStarshiiBrat() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
