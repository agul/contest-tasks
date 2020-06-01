#include "base/header.hpp"

class ANaiboleeNestabilniiMassiv {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll n, m;
		in >> n >> m;
		if (n == 1) {
			out << 0 << std::endl;
			return;
		}
		if (n == 2) {
			out << m << std::endl;
			return;
		}
		out << m * 2 << std::endl;
	}


	ANaiboleeNestabilniiMassiv() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};
