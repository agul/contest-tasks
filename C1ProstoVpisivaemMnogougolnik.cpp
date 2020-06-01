#include "base/header.hpp"

class C1ProstoVpisivaemMnogougolnik {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		n *= 2;
		long double ans = 1.0 / std::tan(PI / n);
		out << std::fixed << std::setprecision(20) << ans << std::endl;
	}


	C1ProstoVpisivaemMnogougolnik() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
