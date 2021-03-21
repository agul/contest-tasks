#include "base/header.hpp"

class FPotion {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        ll x;
        in >> n >> x;
        std::vector<ll> a(n);
        in >> a;

        sort(a);
        ll ans = LINF;

        for (int cnt : inclusiveRange(1, n)) {
            auto dp = make_vector<ll>(cnt + 1, cnt, -1);
            dp[0][0] = 0;
            for (int k : range(n)) {
                for (int i : downrange(cnt)) {
                    for (int j : range(cnt)) {
                        if (dp[i][j] == -1) {
                            continue;
                        }
                        umax(dp[i + 1][(a[k] + j) % cnt], dp[i][j] + a[k]);
                    }
                }
            }
            for (int i : range(cnt)) {
                const ll diff = x - dp[cnt][i];
                if (dp[cnt][i] == -1 || diff % cnt != 0) {
                    continue;
                }
                if (diff / cnt == 3333333325) {
                    debug(cnt, i, dp[cnt][i]);
                }
                umin(ans, diff / cnt);
            }
        }

        out << ans << std::endl;
	}


	FPotion() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
