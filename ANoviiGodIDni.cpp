#include "base/header.hpp"

class ANoviiGodIDni {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int x;
		std::string s;
		in >> x >> s >> s;
		int ans = 0;
		if (s == "week") {
			ans = 52 + (x == 5 || x == 6 ? 1 : 0);
		} else {
			for (int i : range(12)) {
				ans += (get_days_in_month(i, 2016) >= x ? 1 : 0);
			}
		}
		out << ans << std::endl;
	}


	ANoviiGodIDni() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {}

};
