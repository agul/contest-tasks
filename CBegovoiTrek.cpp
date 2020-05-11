#include "base/header.hpp"
#include "string/prefix_function.hpp"

class CBegovoiTrek {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		std::string s, t;
		in >> s >> t;

		const std::string s_reversed(all(reversed(s)));

		const int n = t.length();
		std::vector<int> dp(n + 1, INF);
		std::vector<pii> prev(n + 1, {-1, -1});

		dp[0] = 0;
		std::string tmp = t + "#" + s;
		std::string tmp_reversed = t + "#" + s_reversed;
		size_t s_start = n + 1;
		for (int i : range(n)) {
			auto p = prefix_function(tmp);
			debug(i);
			debug(p);
			for (int j : range(s_start, tmp.size())) {
				const int p_value = p[j];
				if (p_value > 0) {
					if (umin(dp[i + p_value], dp[i] + 1)) {
						prev[i + p_value] = {j - p_value + 1 - s_start, j - s_start};
					}
				}
			}
			auto pr = prefix_function(tmp_reversed);
			debug(pr);
			debug(tmp_reversed);
			for (int j : range(s_start, tmp_reversed.size())) {
				const int p_value = pr[j];
				if (p_value > 0) {
					if (umin(dp[i + p_value], dp[i] + 1)) {
						if (i + p_value == n) {
							debug(i + p_value, dp[i + p_value], j, s_start, j - s_start, j - s_start - p_value + 1);
						}
						prev[i + p_value] = {s.length() - 1 - (j - p_value + 1 - s_start), s.length() - 1 - (j - s_start)};
					}
				}
			}
			tmp = tmp.substr(1);
			tmp_reversed = tmp_reversed.substr(1);
			--s_start;
		}
		debug(dp);

		if (dp[n] == INF) {
			out << -1 << std::endl;
			return;
		}
		std::vector<pii> ans;
		int pos = n;
		while (pos > 0) {
			const int len = std::abs(prev[pos].X - prev[pos].Y) + 1;
			ans.emplace_back(prev[pos]);
			pos -= len;
		}
		out << ans.size() << std::endl;
		for (const auto& it : reversed(ans)) {
			out << it.X + 1 << " " << it.Y + 1 << std::endl;
		}
	}


	CBegovoiTrek() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};
