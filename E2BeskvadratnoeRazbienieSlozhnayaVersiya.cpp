#include "base/header.hpp"
#include "maths/prime.hpp"

class E2BeskvadratnoeRazbienieSlozhnayaVersiya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<int> a(n);
        in >> a;

        for (int& x : a) {
            auto divs = get_prime_divisors_vector(x);
            int value = 1;
            for (const auto& it : divs) {
                if (it.second % 2 == 1) {
                    value *= it.first;
                }
            }
            x = value;
        }

        auto leftmost = make_vector<int>(k + 1, n, -1);
        for (int deletions : inclusiveRange(k)) {
            SafeUnorderedMap<int, int> values;
            int cnt_repeated = 0;
            int left = 0;
            for (int i : range(n)) {
                int& cur_cnt = values[a[i]];
                ++cur_cnt;
                if (cur_cnt > 1) {
                    while (cnt_repeated == deletions) {
                        const int cur_value = a[left];
                        const auto it = values.find(cur_value);
                        it->second -= 1;
                        if (it->second > 0) {
                            --cnt_repeated;
                        }
                        ++left;
                    }
                    ++cnt_repeated;
                }
                leftmost[deletions][i] = left;
            }
        }
        // debug(leftmost);

        auto dp = make_vector<int>(n + 1, k + 1, INF);
        dp[0][0] = 0;
        dp[1][0] = 1;
        for (int i : range(1, n)) {
            for (int deletions : inclusiveRange(k)) {
                for (int prev_deletions : inclusiveRange(deletions)) {
                    const int left = leftmost[deletions - prev_deletions][i];
                    umin(dp[i + 1][deletions], dp[left][prev_deletions] + 1);
                }
            }
        }
        // debug(dp);
        out << *min_element(dp[n]) << std::endl;
	}


	E2BeskvadratnoeRazbienieSlozhnayaVersiya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
