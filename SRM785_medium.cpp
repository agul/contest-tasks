#include "base/header.hpp"

class EllysTwoRatings {
public:
	double getChance(int N, int cur_tc_rating, int cur_cf_rating) {
		const int kMaxRatingChange = 100;
		const int kMaxRating = 1000;

		std::vector<long double> division;
		for (int i = 0; i < kMaxRating; ++i) {
			const int min_rating = std::max(0, i - kMaxRatingChange);
			const int max_rating = std::min(kMaxRating - 1, i + kMaxRatingChange);
			const int diff = max_rating - min_rating + 1;
			division.emplace_back(1.0 / diff);
		}

		--cur_tc_rating;
		--cur_cf_rating;

		auto dp = make_vector<long double>(2, kMaxRating, kMaxRating, 0);

		for (int i = 0; i < kMaxRating; ++i) {
			dp[0][i][i] = 1;
		}

		for (int week = 0; week < N; ++week) {
			int cur = 0;
			int next = 1;


			for (int tc = 0; tc < kMaxRating; ++tc) {
				long double sum = 0;
				for (int cf = 0; cf < std::min(kMaxRating, kMaxRatingChange); ++cf) {
					sum += dp[cur][tc][cf];
				}
				for (int cf = 0; cf < kMaxRating; ++cf) {
					if (cf + kMaxRatingChange < kMaxRating) {
						sum += dp[cur][tc][cf + kMaxRatingChange];
					}
					if (cf - kMaxRatingChange - 1 >= 0) {
						sum -= dp[cur][tc][cf - kMaxRatingChange - 1];
					}
					dp[next][tc][cf] = sum * division[cf];
				}
				dp[next][tc][tc] = 1;
			}
			// debug(dp[next]);

			cur ^= 1;
			next ^= 1;
			for (int cf = 0; cf < kMaxRating; ++cf) {
				long double sum = 0;
				for (int tc = 0; tc < std::min(kMaxRating, kMaxRatingChange); ++tc) {
					sum += dp[cur][tc][cf];
				}
				for (int tc = 0; tc < kMaxRating; ++tc) {
					if (tc + kMaxRatingChange < kMaxRating) {
						sum += dp[cur][tc + kMaxRatingChange][cf];
					}
					if (tc - kMaxRatingChange - 1 >= 0) {
						sum -= dp[cur][tc - kMaxRatingChange - 1][cf];
					}
					dp[next][tc][cf] = sum * division[tc];
				}
				dp[next][cf][cf] = 1;
			}
			// debug(dp[next]);
		}
		return dp[0][cur_tc_rating][cur_cf_rating];
	}
};

class SRM785_medium {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n, a, b;
		in >> n >> a >> b;
		EllysTwoRatings solution;
		out << std::setprecision(16) << solution.getChance(n, a, b) << std::endl;
	}

	static constexpr bool kUseCustomChecker = false;
	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
