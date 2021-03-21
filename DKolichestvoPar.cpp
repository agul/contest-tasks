#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/prime.hpp"

class DKolichestvoPar {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	const int kMaxn = 22222222;

	void solve(std::istream& in, std::ostream& out) {
        ll c, d, x;
        in >> c >> d >> x;

        const auto x_prime_divs = get_prime_divisors_vector<int>(x, min_prime_div);
        auto divs = divisors_vector(x_prime_divs);
        ll ans = 0;
        for (ll div : divs) {
            const ll cg = x + d * div;
            if (cg % c != 0) {
                continue;
            }
            const ll l = cg / c;
            if (l % div != 0) {
                continue;
            }
            // debug(div, l, cnt_divs);
            ans += (1 << cnt_divs[l / div]);
        }
        out << ans << std::endl;
	}

	std::vector<int> min_prime_div;
	std::vector<int> cnt_divs;

	DKolichestvoPar() : cnt_divs(kMaxn, 0) {
	    min_prime_div = min_prime_div_vector<int>(kMaxn);
        cnt_divs[1] = 0;
        for (int i : range(2, kMaxn)) {
            const int prev = i / min_prime_div[i];
            cnt_divs[i] = cnt_divs[prev];
            if (min_prime_div[prev] != min_prime_div[i]) {
                ++cnt_divs[i];
            }
        }
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
