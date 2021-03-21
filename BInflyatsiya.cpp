#include "base/header.hpp"

class BInflyatsiya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        ll k;
        in >> n >> k;
        std::vector<ll> a(n);
        in >> a;

        ll cur = a[0];
        ll ans = 0;
        for (int i : range(1, n)) {
            const ll limit = cur * k / 100;
            if (a[i] > limit) {
                ll min_value = a[i] * 100 / k;
                if (a[i] * 100 % k > 0) {
                    ++min_value;
                }
                ans += min_value - cur;
                cur = min_value;
            }
            cur += a[i];
        }
        out << ans << std::endl;
	}


	BInflyatsiya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
