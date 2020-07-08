#include "base/header.hpp"

class DChatInACircle {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<ll> a(n);
		in >> a;
		sort(a, std::greater<>());
		ll ans = 0;
		for (int i : range(n)) {
			ans += a[i / 2];
		}
		ans -= a.front();
		out << ans << std::endl;
	}


	DChatInACircle() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
