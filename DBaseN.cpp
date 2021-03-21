#include "base/header.hpp"
#include "maths/maths.hpp"

class DBaseN {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	bool check_if_ok(const ll base, const std::string& x, const ll m) {
	    // debug(base, x, m);
        ll value = 0;
        for (char ch : x) {
            if (value > 0 && m / value < base) {
                return false;
            }
            value = value * base + (ch - '0');
            // debug(base, ch, value);
            if (value > m) {
                return false;
            }
        }
        return (value <= m);
	}

	void solve(std::istream& in, std::ostream& out) {
        std::string x;
        ll m;
        in >> x >> m;

        const int max_digit = *max_element(x) - '0';
        const int len = x.length();

        if (len == 1) {
            int ans = 0;
            if (x[0] - '0' <= m) {
                ++ans;
            }
            out << ans << std::endl;
            return;
        }

        if (len <= 4) {
            ll L = max_digit;
            ll R = m + 1;

            if (len == 3) {
                umin(R, (ll)1e9);
            }
            if (len == 4) {
                umin(R, (ll)1e6);
            }

            while (R - L > 1) {
                ll md = (L + R) / 2;
                if (check_if_ok(md, x, m)) {
                    L = md;
                } else {
                    R = md;
                }
            }
            if (check_if_ok(R, x, m)) {
                ++L;
            }
            out << L - max_digit << std::endl;
            return;
        }

        int cnt = 0;
        for (int base : range(max_digit + 1, 33333)) {
            if (check_if_ok(base, x, m)) {
                ++cnt;
                debug(base);
            }
        }
        out << cnt << std::endl;
	}


	DBaseN() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
