#include "base/header.hpp"
#include "maths/prime.hpp"

class ANechetniiDelitel {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        ll n;
        in >> n;
        while (n % 2 == 0) {
            n /= 2;
        }
        if (n != 1) {
            out << "YES" << std::endl;
        } else {
            out << "NO" << std::endl;
        }
	}


	ANechetniiDelitel() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
