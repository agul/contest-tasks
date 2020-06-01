#include "base/header.hpp"

class ASchetniePalochki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		in >> s;

		int a = s.find('+');
		int b = s.find('=');

		const int c = s.length() - b - 1;
		b -= a + 1;

		auto check = [&out](const int a, const int b, const int c) {
			if (a < 1 || b < 1 || c < 1) {
				return false;
			}
			if (a + b == c) {
				out << std::string(a, '|') << "+" << std::string(b, '|') << "=" << std::string(c, '|') << std::endl;
				return true;
			}
			return false;
		};

		if (check(a, b, c) || check(a - 1, b, c + 1) || check(a, b - 1, c + 1) || check(a + 1, b, c - 1)) {
			return;
		}
		out << "Impossible" << std::endl;

	}


	ASchetniePalochki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
