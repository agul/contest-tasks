#include "base/header.hpp"

class DTsvetniePryamougolniki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int r, g, b;
        in >> r >> g >> b;
        std::vector<ll> red(r);
        std::vector<ll> green(g);
        std::vector<ll> blue(b);

        in >> red >> green >> blue;

        sort(red, std::greater<>());
        sort(green, std::greater<>());
        sort(blue, std::greater<>());

        auto dp = make_vector<ll>(r + 1, g + 1, b + 1, 0);
        ll ans = 0;
        for (int rc : inclusiveRange(r)) {
            for (int gc : inclusiveRange(g)) {
                for (int bc : inclusiveRange(b)) {
                    umax(ans, dp[rc][gc][bc]);
                    debug(rc, gc, bc, dp[rc][gc][bc]);
                    if (rc < r && gc < g) {
                        umax(dp[rc + 1][gc + 1][bc], dp[rc][gc][bc] + red[rc] * green[gc]);
                    }
                    if (rc < r && bc < b) {
                        umax(dp[rc + 1][gc][bc + 1], dp[rc][gc][bc] + red[rc] * blue[bc]);
                    }
                    if (bc < b && gc < g) {
                        umax(dp[rc][gc + 1][bc + 1], dp[rc][gc][bc] + blue[bc] * green[gc]);
                    }
                }
            }
        }
        out << ans << std::endl;
	}


	DTsvetniePryamougolniki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
