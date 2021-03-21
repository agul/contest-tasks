#include "base/header.hpp"

class CMinimalniiPutNaPole {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<ll> a(n);
        in >> a;

        auto cnt = make_vector<ll>(n + 1, 2, 0);
        auto min = make_vector<ll>(n + 1, 2, LINF);
        auto sum = make_vector<ll>(n + 1, 2, 0);

        for (int i : range(n)) {
            cnt[i + 1] = cnt[i];
            min[i + 1] = min[i];
            sum[i + 1] = sum[i];

            sum[i + 1][i % 2] += a[i];
            umin(min[i + 1][i % 2], a[i]);
            cnt[i + 1][i % 2] += 1;
        }

        debug(n);
        debug(cnt[n]);
        debug(min[n]);
        debug(sum[n]);

        ll ans = LINF;
        for (int i : range(2, n + 1)) {
            ll cur = 0;
            for (int mod : range(2)) {
                cur += (n - cnt[i][mod]) * min[i][mod] + sum[i][mod];
            }
            umin(ans, cur);
        }
        out << ans << std::endl;
	}


	CMinimalniiPutNaPole() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
