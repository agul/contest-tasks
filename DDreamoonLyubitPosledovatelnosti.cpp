#include "base/header.hpp"

class DDreamoonLyubitPosledovatelnosti {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	int ans = 0;

	void go(const int prev, const int max, std::vector<int>& a, std::vector<int>& b) {
	    ++ans;
	    debug(a);
	    for (int value : inclusiveRange(prev + 1, max)) {
	        const int new_b_value = (b.back() ^ value);
            if (new_b_value >= b.back()) {
                a.emplace_back(value);
                b.emplace_back(new_b_value);
                go(value, max, a, b);
                a.pop_back();
                b.pop_back();
            }
	    }
	}

	void solve(std::istream& in, std::ostream& out) {
	    /*
	    int n;
	    in >> n;
	    for (int start : inclusiveRange(1, n)) {
            std::vector<int> a = {start};
            std::vector<int> b = {start};
            go(start, n, a, b);
	    }
	    out << ans << std::endl;
	     */
	    ll n, mod;
	    in >> n >> mod;
	    std::vector<ll> cnt;
	    ll prev_power = 1;
	    ll power = 2;
	    for (int i : range(32)) {
	        cnt.emplace_back(std::max(0LL, std::min(n - prev_power + 1, power - prev_power)));
	        prev_power = power;
	        power *= 2;
	    }
	    debug(cnt);

	    std::vector<ll> dp(32, 0);
	    dp[0] = 1;
	    for (int i : range(32)) {
	        if (cnt[i] == 0) {
	            break;
	        }
	        for (int len : downrange(i + 1)) {
                dp[len + 1] += dp[len] * cnt[i];
                dp[len + 1] %= mod;
	        }
	    }
        debug(dp);

        const ll ans = std::accumulate(dp.begin() + 1, dp.end(), 0LL) % mod;
	    out << ans << std::endl;
	}


	DDreamoonLyubitPosledovatelnosti() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
