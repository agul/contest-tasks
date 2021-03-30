#include "base/header.hpp"

class AOddVsEven {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        ll n;
        in >> n;
        if (n % 4 != 0 && n % 2 == 0) {
            out << "Same" << std::endl;
        }
        else if (n % 4 == 0) {
            out << "Even" << std::endl;
        } else {
            out << "Odd" << std::endl;
        }
	}


	AOddVsEven() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
