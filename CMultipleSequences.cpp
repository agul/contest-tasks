#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/mod_int.hpp"

class CMultipleSequences {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

    using Int = ModInt<int, 998244353>;

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;

        Int ans = 0;
        for (int i : inclusiveRange(1, m)) {
            for (int j : inclusiveRange(1, std::min(kMaxDivs - 1, n))) {
                const Int comb = combinations_with_repetitions(j, n - j);
                // debug(i, j, n - j, comb, dp[j][i]);
                ans += comb * dp[j][i];
            }
        }
        out << ans << std::endl;
	}

	const int kMaxDivs = 20;
	static constexpr int kMaxn = 222222;

	std::vector<std::vector<int>> divisors;
	std::vector<std::vector<Int>> dp;
	std::vector<Int> factorial;

	Int binom(const int n, const int k) const {
	    return factorial[n] * factorial[k].inverse() * factorial[n - k].inverse();
	}

	Int combinations_with_repetitions(const int n, const int k) const {
        return binom(n + k - 1, k);
	}

	CMultipleSequences() : divisors(kMaxn) {
	    for (int i : range(1, kMaxn)) {
	        divisors[i] = divisors_vector(i);
	    }

	    factorial = calc_factorial<Int>(kMaxn * 2);

	    dp = make_vector<Int>(kMaxDivs + 1, kMaxn, 0);
        dp[0][1] = 1;
        dp[1][1] = 1;
        for (int i : range(2, kMaxn)) {
            for (int divs_cnt : downrange(kMaxDivs)) {
                for (int last : divisors[i]) {
                    dp[divs_cnt + 1][i] += dp[divs_cnt][last];
                }
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
