#include "base/header.hpp"
#include "maths/maths.hpp"

class DPokupkaLopat {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		auto a = divisors_vector(n);
		int ans = n;
		for (int x : a) {
			if (x <= k) {
				umin(ans, n / x);
			}
		}
		out << ans << std::endl;
	}


	DPokupkaLopat() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
