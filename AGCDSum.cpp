#include "base/header.hpp"
#include "maths/maths.hpp"

class AGCDSum {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        ll n;
        in >> n;
        while (true) {
            const int digits_sum = digit_sum(n);
            if (gcd<ll>(digits_sum, n) > 1) {
                out << n << std::endl;
                return;
            }
            ++n;
        }
	}


	AGCDSum() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
