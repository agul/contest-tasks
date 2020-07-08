#include "base/header.hpp"

class BJudgeStatusSummary {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<std::string> a(n);
		in >> a;

		out << "AC x " << std::count(all(a), "AC") << std::endl;
		out << "WA x " << std::count(all(a), "WA") << std::endl;
		out << "TLE x " << std::count(all(a), "TLE") << std::endl;
		out << "RE x " << std::count(all(a), "RE") << std::endl;
	}


	BJudgeStatusSummary() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
