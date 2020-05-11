#include "base/header.hpp"
#include "maths/mod_int.hpp"
#include "string/utils.hpp"
#include "hash/hasher.hpp"

class DNoviiGodIDrevneeProrochestvo {
public:
	using Int = ModInt<int, 1000000007>;

	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		std::string s;
		in >> n >> s;

		auto dp = make_vector<Int>(n, n, 0);
		dp[0][0] = 1;

		Hasher<DoubleHasher<int>> hasher(s);

		for (int L : range(n)) {
			for (int R : range(L, n - 1)) {
				dp[L][R + 1] += dp[L][R];
				const int len = R - L + 1;
				const int start = R + 1;
				const int finish = R + len;

				if (finish >= n || s[start] == '0') {
					continue;
				}

				const int max_prefix_length = hasher.lcp(L, start);
				const int first_to_cmp = start + max_prefix_length;

				int need_len = len;
				if (max_prefix_length >= len || s[first_to_cmp] < s[L + max_prefix_length]) {
					++need_len;
				}
				if (R + need_len < n) {
					dp[R + 1][R + need_len] += dp[L][R];
				}
			}
		}

		Int ans = 0;
		for (int i : range(n)) {
			ans += dp[i][n - 1];
		}
		out << ans << std::endl;
	}


	DNoviiGodIDrevneeProrochestvo() {}

	ll solve_slow(const std::string& s, const int index, const ll cur_value, const ll prev_value) const {
		if (index == s.size()) {
			if (cur_value > prev_value) {
				// // debug(cur_value, prev_value);
			}
			return (cur_value > prev_value ? 1 : 0);
		}
		ll ans = solve_slow(s, index + 1, cur_value * 10 + to_digit(s[index]), prev_value);
		if (cur_value > prev_value && s[index] != '0') {
			ans += solve_slow(s, index + 1, to_digit(s[index]), cur_value);
		}
		return ans;
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n;
		std::string s;
		in >> n >> s;

		ll pans;
		out >> pans;

		ll jans = solve_slow(s, 1, to_digit(s.front()), 0);
		if (jans != pans) {
			// debug(jans, pans);
			return false;
		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 15;

		const int n = Random::get(1, kMaxn);
		std::string input;
		for (int i : range(n)) {
			input += Random::get(0, 9) + '0';
		}
		if (input.front() == '0') {
			++input.front();
		}
		test << n << std::endl << input << std::endl;
	}

};
