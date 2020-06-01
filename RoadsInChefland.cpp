#include "base/header.hpp"
#include "maths/bits.hpp"

class RoadsInChefland {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll n;
		in >> n;
		if (has_single_bit(n)) {
			out << -1 << std::endl;
			return;
		}
		ll ans = 0;
		for (int i : range(30)) {
			const ll deg = 1 << i;
			ans += (n / deg - n / (deg * 2)) * deg;
		}
		out << ans - 1 << std::endl;
	}


	RoadsInChefland() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
