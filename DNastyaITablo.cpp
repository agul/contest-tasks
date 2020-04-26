#include "base/header.hpp"

const std::unordered_map<std::string, int> digits{
	{"1110111", 0},
	{"0010010", 1},
	{"1011101", 2},
	{"1011011", 3},
	{"0111010", 4},
	{"1101011", 5},
	{"1101111", 6},
	{"1010010", 7},
	{"1111111", 8},
	{"1111011", 9}
};

class DNastyaITablo {
public:
	DNastyaITablo() : vals(10) {
		for (const auto& it : digits) {
			vals[it.second] = it.first;
		}
	}

	int intersect(const std::string& from, const std::string& to) const {
		int cnt = 0;
		for (int ind : range(7)) {
			if (to[ind] == '0' && from[ind] == '1') {
				return -1;
			}
			if (to[ind] == '1' && from[ind] == '0') {
				++cnt;
			}
		}
		return cnt;
	}

	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		std::vector<std::string> a(n);
		in >> a;
		reverse(a);

		auto ways = make_vector<int>(n, 10, -1);
		for (int i : range(n)) {
			for (int j : range(10)) {
				ways[i][j] = intersect(a[i], vals[j]);
			}
		}

		auto dp = make_vector<int>(n + 1, k + 1, -1);
		dp[0][0] = 0;
		for (int i : range(n)) {
			for (int j : range(k + 1)) {
				if (dp[i][j] == -1) {
					continue;
				}
				for (int to : range(10)) {
					if (ways[i][to] >= 0) {
						const int next = j + ways[i][to];
						if (next <= k) {
							dp[i + 1][next] = to;
						}
					}
				}
			}
		}

		if (dp[n][k] == -1) {
			out << -1 << std::endl;
			return;
		}

		std::vector<int> ans(n, -1);
		int cur = k;
		int pos = n;
		while (pos > 0) {
			--pos;
			for (int i : downrange(10)) {
				const int len = ways[pos][i];
				if (len == -1) {
					continue;
				}
				if (cur - len >= 0 && dp[pos][cur - len] != -1) {
					ans[pos] = i;
					cur -= len;
					break;
				}
			}
		}

		reverse(ans);
		for (const int x : ans) {
			out << x;
		}
		out << std::endl;
	}

	std::string solve_slow(const int n, const int k, const std::vector<std::string>& a) const {
		int ans = -1;

		std::function<void(int, int, int)> dfs = [&ans, &a, this, &dfs](const int pos, const int val, const int k) {
			// debug(pos, val, k);
			const std::string& from = a[pos];
			for (int i : range(10)) {
				const std::string& to = vals[i];
				const int cnt = intersect(from, to);
				if (cnt > k || cnt == -1) {
					continue;
				}
				const int cur_val = val * 10 + i;
				if (k == cnt && pos + 1 == a.size()) {
					umax(ans, cur_val);
					continue;
				}
				if (pos + 1 < a.size()) {
					dfs(pos + 1, cur_val, k - cnt);
				}
			}
		};
		dfs(0, 0, k);
		if (ans == -1) {
			return "-1";
		}
		const std::string res = std::to_string(ans);
		return std::string(a.size() - res.size(), '0') + res;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		std::istringstream in(input);
		std::istringstream out(actual_output);
		int n, k;
		in >> n >> k;
		std::vector<std::string> a(n);
		in >> a;

		const auto ans = solve_slow(n, k, a);
		std::string output_str;
		out >> output_str;
		debug(output_str, ans);
		return output_str == ans;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {
		int n = rand() % 7 + 1;

		std::vector<std::string> input(n);
		for (auto& str : input) {
			const int cur_digit = rand() % 10;
			for (const auto& it : digits) {
				if (it.second == cur_digit) {
					str = it.first;
					break;
				}
			}
		}

		int k = 0;
		int prob = rand() % 10 + 1;
		for (auto& str : input) {
			for (auto& ch : str) {
				if (ch == '1' && rand() % prob == 0) {
					ch = '0';
					++k;
				}
			}
		}

		test << n << " " << k << std::endl;
		for (const auto& str : input) {
			test << str << std::endl;
		}
	}

private:
	std::vector<std::string> vals;
	size_t test_id_ = 0;
};
