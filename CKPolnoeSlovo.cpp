#include "base/header.hpp"

class CKPolnoeSlovo {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	std::vector<bool> used;
	std::vector<int> cnt;
	std::string s;
	int n, k;

	void dfs(const int v) {
		used[v] = true;
		++cnt[s[v] - 'a'];

		auto check = [&](const int v) {
			return v >= 0 && v < n && !used[v];
		};

		if (check(v - k)) {
			dfs(v - k);
		}
		if (check(v + k)) {
			dfs(v + k);
		}
		if (check(n - 1 - v)) {
			dfs(n - 1 - v);
		}
	}

	void solve(std::istream& in, std::ostream& out) {
		in >> n >> k >> s;
		int ans = 0;
		used.assign(n, false);
		for (int i : range(k)) {
			if (!used[i]) {
				cnt.assign(26, 0);
				dfs(i);
				const int total = std::accumulate(all(cnt), 0LL);
				const int mx = *max_element(cnt);
				ans += total - mx;
			}
		}
		out << ans << std::endl;
	}


	CKPolnoeSlovo() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
