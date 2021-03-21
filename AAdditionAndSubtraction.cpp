#include "base/header.hpp"

class AAdditionAndSubtraction {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int a, b;
        in >> a >> b;
        out << a + b << " " << std::min(a, b) - std::max(a, b) << std::endl;
	}


	AAdditionAndSubtraction() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
