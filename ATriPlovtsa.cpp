#include "base/header.hpp"

class ATriPlovtsa {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        ll p, a, b, c;
        in >> p >> a >> b >> c;

        auto calc = [&p](const ll x) {
            const ll mod = p % x;
            if (mod == 0) {
                return 0LL;
            }
            return x - mod;
        };

        ll ans = std::min({calc(a), calc(b), calc(c)});
        out << ans << std::endl;
	}


	ATriPlovtsa() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
