#include "base/header.hpp"

class AMinimalniiKvadrat {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int a, b;
		in >> a >> b;
		int ans = std::min(
			std::max(a, b * 2),
			std::max(a * 2, b)
		);
		out << ans * ans << std::endl;
	}


	AMinimalniiKvadrat() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
