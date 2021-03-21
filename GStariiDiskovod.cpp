#include "base/header.hpp"

class GStariiDiskovod {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<ll> a(n);
        in >> a;

        std::vector<pli> fastest_sums;
        ll mx_sum = 0;
        ll cur_sum = 0;
        for (int i : range(n)) {
            cur_sum += a[i];
            if (cur_sum > mx_sum) {
                fastest_sums.emplace_back(cur_sum, i);
                mx_sum = cur_sum;
            }
        }

        for (int i : range(m)) {
            ll x;
            in >> x;

            if (mx_sum >= x) {
                auto it = std::lower_bound(all(fastest_sums), pli(x, -1));
                out << it->second << " ";
                continue;
            }

            if (cur_sum <= 0) {
                out << -1 << " ";
                continue;
            }

            const ll diff = x - mx_sum;
            const ll count = ((diff - 1) / cur_sum + 1);
            ll ans = count * n;

            auto it = std::lower_bound(all(fastest_sums), pli(x - cur_sum * count, -1));
            out << ans + it->second << " ";
        }
        out << std::endl;
	}


	GStariiDiskovod() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
