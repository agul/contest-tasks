#include "base/header.hpp"

class AMagaziniPonchikov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll a, b, c;
		in >> a >> b >> c;
		if (a < c) {
			out << 1 << " ";
		} else {
			out << -1 << " ";
		}

		if (c < b * a) {
			out << b << " ";
		} else {
			out << -1 << " ";
		}
		out << std::endl;
	}


	AMagaziniPonchikov() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
