#include "base/header.hpp"
#include "maths/mod_int.hpp"
#include "maths/bits.hpp"

class DIWannaWinTheGame {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

    using Int = ModInt<int, 998244353>;

    static constexpr int kMaxn = 5555;
    static constexpr int kMaxBinaryDegree = binary_power(kMaxn);
    static constexpr int kMaxXor = (1 << (kMaxBinaryDegree + 1));

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;

        /*
        auto dp = make_vector<Int>(kMaxn, kMaxXor, 0);
        auto used = make_vector<bool>(kMaxn, kMaxXor, false);
        dp[0][0] = 1;
        used[0][0] = true;
        for (int value : range(1, kMaxn)) {
            if (value % 10 == 0) {
                std::cerr << value << std::endl;
            }
            for (int sum : downrange(kMaxn - value)) {
                const int newsum = sum + value;
                for (int cur_xor : range(kMaxXor)) {
                    if (!used[sum][cur_xor]) {
                        continue;
                    }
                    const int newxor = cur_xor ^ value;
                    used[newsum][newxor] = true;
                    dp[newsum][newxor] += dp[sum][cur_xor];
                }
            }
        }

        for (int sum : range(kMaxn)) {
            out << dp[sum][0] << ",";
        }
        out << std::endl;

         */

        /*
        auto dp = make_vector<Int>(kMaxn + 1, kMaxn + 1, kMaxXor, 0);
        dp[0][0][0] = 1;
        for (int cnt : range(kMaxn)) {
            for (int sum : range(kMaxn)) {
                for (int curxor : range(kMaxXor)) {
                    if (dp[cnt][sum][curxor] == 0) {
                        continue;
                    }
                    for (int value : range(1, kMaxn)) {
                        if (sum + value >= kMaxn) {
                            continue;
                        }
                        dp[cnt + 1][sum + value][curxor ^ value] += dp[cnt][sum][curxor];
                    }
                }
            }
        }
        for (int cnt : inclusiveRange(kMaxn)) {
            std::vector<Int> tmp;
            for (int sum : inclusiveRange(kMaxn)) {
                // debug(cnt, sum, dp[cnt][sum][0]);
                tmp.emplace_back(dp[cnt][sum][0]);
            }
            debug(cnt, tmp);
        }
         */

        debug(kMaxBinaryDegree);
        auto dp = make_vector<Int>(kMaxBinaryDegree + 2, kMaxn, 0);
        dp[0][0] = 1;
        for (int degree : inclusiveRange(kMaxBinaryDegree)) {
            const int delta = (1 << degree);
            for (int sum : range(kMaxn)) {
                if (dp[degree][sum] == 0) {
                    continue;
                }
                for (int cnt : inclusiveRange(n)) {
                    const int newsum = sum + delta * cnt * 2;
                    if (newsum >= kMaxn || cnt * 2 > n) {
                        break;
                    }
                    dp[degree + 1][newsum] += dp[degree][sum] * binom(n, cnt * 2);
                }
            }
        }
        out << dp.back()[m] << std::endl;
	}

    std::vector<Int> factorial;

    Int binom(const int n, const int k) const {
        return factorial[n] * factorial[k].inverse() * factorial[n - k].inverse();
    }

	DIWannaWinTheGame() {
        factorial = calc_factorial<Int>(kMaxn);
    }


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
