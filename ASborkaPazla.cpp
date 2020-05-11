#include "base/header.hpp"

class ASborkaPazla {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int a, b;
		in >> a >> b;
		if (a == 1 || b == 1 || (a == 2 && b == 2)) {
			out << "YES" << std::endl;
			return;
		}
		out << "NO" << std::endl;
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {}

};
