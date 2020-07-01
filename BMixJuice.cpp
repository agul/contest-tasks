#include "base/header.hpp"

class BMixJuice {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		std::vector<int> a(n);
		in >> a;

		sort(a);

		ll ans = 0;
		for (int i : range(k)) {
			ans += a[i];
		}
		out << ans << std::endl;
	}


	BMixJuice() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
