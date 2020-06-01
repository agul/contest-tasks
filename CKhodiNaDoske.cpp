#include "base/header.hpp"
#include "maths/maths.hpp"

class CKhodiNaDoske {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll n;
		in >> n;

		bool even = false;
		if (n % 2 == 0) {
			--n;
			even = true;
		}
		ll ans = 0;
		ll prev = 0;
		for (ll i : inclusiveRange(n / 2)) {
			const ll cells = sqr(2 * i + 1);
			ans += (cells - prev) * i;
			prev = cells;
		}
		if (even) {
			++n;
			ans += (2 * n - 1) * n / 2;
		}
		out << ans << std::endl;
	}


	CKhodiNaDoske() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};
