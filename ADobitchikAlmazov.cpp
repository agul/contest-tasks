#include "base/header.hpp"
#include "maths/maths.hpp"

class ADobitchikAlmazov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<ll> diamonds;
        std::vector<ll> miners;
        for (int i : range(2 * n)) {
            ll x, y;
            in >> x >> y;
            if (x == 0) {
                miners.emplace_back(y);
            } else {
                diamonds.emplace_back(x);
            }
        }
        sort(diamonds, [](const ll lhs, const ll rhs) {
            return std::abs(lhs) < std::abs(rhs) || std::abs(lhs) == std::abs(rhs) && lhs < rhs;
        });

        sort(miners, [](const ll lhs, const ll rhs) {
            return std::abs(lhs) < std::abs(rhs) || std::abs(lhs) == std::abs(rhs) && lhs < rhs;
        });

        ld ans = 0;
        for (int i : range(n)) {
            ans += sqrt(sqr(diamonds[i]) + sqr(miners[i]));
        }
        out << ans << std::endl;
	}


	ADobitchikAlmazov() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
