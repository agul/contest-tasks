#include "base/header.hpp"

class AStrannayaTablitsa {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        ll n, m, x;
        in >> n >> m >> x;
        --x;

        ll row = x % n;
        ll col = x / n;

        out << row * m + col + 1 << std::endl;
	}


	AStrannayaTablitsa() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
