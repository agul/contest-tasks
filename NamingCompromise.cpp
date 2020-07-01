#include "base/header.hpp"

class NamingCompromise {
public:
	static constexpr bool kWriteCaseNumber = true;
	static constexpr bool kMultiTest = true;

	static int edit_distance(const std::string& s, const std::string& t, std::vector<std::vector<int>>* distance = nullptr) {
		const int n = s.length();
		const int m = t.length();
		auto dp = make_vector<int>(n + 1, m + 1, INF);
		dp[0][0] = 0;
		for (int i : range(1, n + 1)) {
			dp[i][0] = i;
		}
		for (int j : range(1, m + 1)) {
			dp[0][j] = j;
		}
		for (int i : range(1, n + 1)) {
			for (int j : range(1, m + 1)) {
				if (s[i - 1] == t[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				} else {
					dp[i][j] = std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
				}
			}
		}
		const size_t result = dp[n][m];
		if (distance != nullptr) {
			distance->swap(dp);
		}
		return result;
	}

	void solve(std::istream& in, std::ostream& out) {
		std::string s, t;
		in >> s >> t;

		const int n = s.length();
		const int m = t.length();
		auto dp = make_vector<int>(n + 1, m + 1, INF);
		edit_distance(s, t, &dp);

		for (int i : range(n + 1)) {
			// debug(dp[i]);
		}
		// out << dp[n][m] << std::endl;

		const int total_distance = dp[n][m];
		int x = n;
		int y = m;
		int pos = total_distance / 2;

		std::vector<std::pair<int, char>> chars;
		for (int i : range(n)) {
			chars.emplace_back(i, s[i]);
		}

		auto chars_to_ans = [&chars]() {
			std::string ans;
			for (const auto& it : chars) {
				if (it.second != '$') {
					ans += it.second;
				}
			}
			return ans;
		};

		// debug(chars);

		while (pos > 0 && (x > 0 || y > 0)) {
			const int cur_value = dp[x][y];

			const auto iter = std::find_if(all(chars), [x](const auto& it) {
				return it.first == x - 1;
			});
			// debug("found", iter->first);

			if (x > 0 && y > 0 && cur_value == dp[x - 1][y - 1] && iter->second == t[y - 1]) {
				// debug("action:skip", chars);
				--x;
				--y;
				continue;
			}
			if (x > 0 && y > 0 && cur_value == dp[x - 1][y - 1] + 1) {
				iter->second = t[y - 1];
				// debug("action:modify", chars);
				--x;
				--y;
				--pos;
				continue;
			}
			if (x > 0 && dp[x - 1][y] + 1 == cur_value) {
				iter->second = '$';
				// debug("action:delete", chars);
				--pos;
				--x;
				continue;
			}
			if (y > 0 && dp[x][y - 1] + 1 == cur_value) {
				chars.insert(chars.cbegin() + x, std::make_pair(-1, t[y - 1]));
				// debug("action:insert", chars);
				--pos;
				--y;
				continue;
			}
			assert(false);
		}

		const std::string ans = chars_to_ans();

		out << ans << std::endl;
	}


	NamingCompromise() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;
		for (int test_id : range(1, testsCount + 1)) {
			std::string s, t;
			in >> s >> t;

			std::string skip;
			std::string pans;
			out >> skip >> skip >> pans;

			const int jans = edit_distance(s, t);
			const int s_dist = edit_distance(s, pans);
			const int t_dist = edit_distance(t, pans);

			if (std::abs(s_dist - t_dist) > 1) {
				debug("FAIL", test_id, s_dist, t_dist);
				return false;
			}

			if (jans != s_dist + t_dist) {
				debug("FAIL", test_id, jans, s_dist + t_dist);
				return false;
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int testsCount = 100;
		const int kMaxn = 50;
		test << testsCount << std::endl;
		for (int i : range(testsCount)) {
			const int n = Random::get(1, kMaxn);
			const int m = Random::get(1, kMaxn);
			for (int j : range(n)) {
				test << (char)('A' + Random::get(0, 26));
			}
			test << " ";
			for (int j : range(m)) {
				test << (char)('A' + Random::get(0, 26));
			}
			test << std::endl;
		}
	}

};
