#include "base/header.hpp"

class AC {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll a, b, n;
		in >> a >> b >> n;
		if (a < b) {
			std::swap(a, b);
		}
		int ans = 0;
		while (a <= n) {
			b += a;
			std::swap(a, b);
			++ans;
		}
		out << ans << std::endl;
	}


	AC() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
