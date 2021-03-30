#include "base/header.hpp"

class DGenii {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	static ll solve_hard(const std::vector<int>& tags, const std::vector<ll>& diff) {
	    const int n = tags.size();
        auto dp = make_vector<ll>(2, n + 1, 0);
        auto right_only = make_vector<ll>(2, n + 1, 0);
        ll ans = 0;
        int cur_row = 1;
        for (int i : range(1, n)) {
            const int prev_row = cur_row ^ 1;
            // debug(i, dp[prev_row]); debug(i, right_only[prev_row]);
            dp[cur_row] = dp[prev_row];
            right_only[cur_row] = right_only[prev_row];
            dp[cur_row].assign(n + 1, 0);
            for (int j : downrange(i)) {
                if (tags[j] != tags[i]) {
                    if (umax(dp[cur_row][j], right_only[prev_row][j] + std::abs(diff[i] - diff[j]))) {
                        umax(right_only[cur_row][i], dp[cur_row][j]);
                    }
                }
            }
            // debug(i, dp[cur_row]);
            ll prev_max = 0;
            ll cur_max = 0;
            for (int j : downrange(i)) {
                if (tags[j] != tags[i - 1] && tags[j] != tags[i]) {
                    umax(dp[cur_row][j], prev_max + std::abs(diff[i - 1] - diff[j]) + std::abs(diff[i] - diff[j]));
                }
                // debug(i, j, dp[cur_row][j]);
                if (tags[i] != tags[j]) {
                    umax(right_only[cur_row][j], cur_max + std::abs(diff[i] - diff[j]));
                }
                umax(cur_max, dp[cur_row][j]);
                umax(prev_max, dp[prev_row][j]);
            }
            umax(ans, *max_element(dp[cur_row]));
            umax(ans, *max_element(right_only[cur_row]));
            cur_row ^= 1;
        }
        return ans;
	}

    static ll solve_medium(const std::vector<int>& tags, const std::vector<ll>& diff) {
        const int n = tags.size();
        auto dp = make_vector<ll>(2, n + 1, 0);
        ll ans = 0;
        int cur_row = 1;
        for (int i : range(1, n)) {
            const int prev_row = cur_row ^ 1;
            dp[cur_row] = dp[prev_row];
            for (int j : downrange(i)) {
                if (tags[i] != tags[j]) {
                    umax(dp[cur_row][j], dp[cur_row][i] + std::abs(diff[i] - diff[j]));
                    umax(dp[cur_row][i], dp[prev_row][j] + std::abs(diff[i] - diff[j]));
                }
            }
            umax(ans, *max_element(dp[cur_row]));
            cur_row ^= 1;
        }
        return ans;
    }

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> tags(n);
        std::vector<ll> diff(n);
        in >> tags >> diff;

        out << solve_medium(tags, diff) << std::endl;
	}


	DGenii() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    int testsCount;
	    in >> testsCount;
	    for (int test : range(testsCount)) {
            int n;
            in >> n;
            std::vector<int> tags(n);
            std::vector<ll> score(n);
            in >> tags >> score;

            tags.insert(tags.begin(), -1);
            score.insert(score.begin(), -1);

            auto diff = make_vector<ll>(n + 1, n + 1, 0);
            for (int i : inclusiveRange(1, n)) {
                for (int j : inclusiveRange(1, n)) {
                    diff[i][j] = std::abs(score[i] - score[j]);
                }
            }

            ll jans = 0;
            auto dp = make_vector<ll>(n + 1, n + 1, 0);
            for (int i : inclusiveRange(1, n)) {
                for (int from : range(1, i)) {
                    if (tags[i] != tags[from]) {
                        const ll max = *max_element(dp[from]);
                        umax(dp[i][from], max + diff[i][from]);
                    }
                    for (int prev : inclusiveRange(1, from)) {
                        for (int via : range(1, prev)) {
                            if (tags[via] != tags[from] && tags[via] != tags[i]) {
                                umax(dp[i][via], dp[from][prev] + diff[from][via] + diff[via][i]);
                            }
                        }
                    }
                }
                umax(jans, *max_element(dp[i]));

                for (int from : range(1, i)) {
                    for (int to : range(1, from)) {
                        if (tags[i] != tags[to]) {
                            umax(jans, dp[i][from] + diff[i][to]);
                        }
                    }
                }
            }

            ll pans;
            out >> pans;

            if (jans != pans) {
                debug(test, jans, pans);
                return false;
            }
        }
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kTestsCount = 10;
	    const int kMaxn = 20;
	    const int kMaxDiff = 20;

	    test << kTestsCount << std::endl;
	    for (int _ : range(kTestsCount)) {
            const int n = Random::get(1, kMaxn);
            test << n << std::endl;
            for (int i : range(n)) {
                test << Random::get(1, n) << " ";
            }
            test << std::endl;
            for (int i : range(n)) {
                test << Random::get(1, kMaxDiff) << " ";
            }
            test << std::endl;
	    }
	}

};
