#include "base/header.hpp"

class ABudilnik {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll a, b, c, d;
		in >> a >> b >> c >> d;
		ll ans = b;
		if (ans >= a) {
			out << ans << std::endl;
			return;
		}
		ll diff = c - d;
		if (diff <= 0) {
			out << -1 << std::endl;
			return;
		}
		ll sleep_cycles = (a - b - 1) / diff + 1;
		ans += sleep_cycles * c;
		out << ans << std::endl;
	}


	ABudilnik() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
