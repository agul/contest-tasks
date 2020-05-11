#include "base/header.hpp"

class BKvadrat {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int a, b, c, d;
		in >> a >> b >> c >> d;

		auto check = [](const int a, const int b, const int c, const int d) {
			return a == b && (c + d) == a;
		};

		if (check(a, c, b, d) || check(a, d, b, c) || check(b, c, a, d) || check(b, d, a, c)) {
			out << "Yes" << std::endl;
		} else {
			out << "No" << std::endl;
		}

	}


	BKvadrat() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {}

};
