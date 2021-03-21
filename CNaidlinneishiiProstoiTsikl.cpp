#include "base/header.hpp"

class CNaidlinneishiiProstoiTsikl {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<ll> c(n);
        std::vector<int> a(n), b(n);
        in >> c >> a >> b;

        for (int i : range(n)) {
            if (a[i] > b[i]) {
                std::swap(a[i], b[i]);
            }
        }

        ll ans = 0;
        ll cur = 0;
        for (int i : range(1, n)) {
            const ll x = a[i];
            const ll y = b[i];
            const ll prev_size = c[i - 1];

            if (i == 1) {
                cur = std::abs(x - y);
            }
            else if (x == y) {
                cur = 0;
            }
            else {
                cur = std::max(cur + (x - 1) + (prev_size - y), std::abs(x - y));
            }
            cur += 2;
            umax(ans, cur + c[i] - 1);
            debug(i, cur, ans);
        }

        out << ans << std::endl;
	}


	CNaidlinneishiiProstoiTsikl() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
