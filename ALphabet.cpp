#include "base/header.hpp"

class ALphabet {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		char ch;
		in >> ch;
		if (ch >= 'A' && ch <= 'Z') {
			out << 'A' << std::endl;
		} else {
			out << 'a' << std::endl;
		}
	}


	ALphabet() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
