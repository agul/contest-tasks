#include "base/header.hpp"

class FVkusnayaPechenka {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<ll> a(n);
		std::vector<ll> b(n);
		in >> a >> b;

		auto ans_to_string = [](const std::vector<ll>& actions) {
			const ll prefsum_count = std::accumulate(all(actions), 0LL);
			if (prefsum_count > 200000) {
				return "BIG\n" + std::to_string(prefsum_count);
			}
			std::string ans;
			for (const auto& action : actions) {
				if (action == 0) {
					ans += 'R';
				} else {
					ans += std::string(action, 'P');
				}
			}
			reverse(ans);
			return "SMALL\n" + std::to_string(ans.length()) + "\n" + ans;
		};

		if (n == 1) {
			out << (a.front() != b.front() ? "IMPOSSIBLE" : ans_to_string({})) << std::endl;
			return;
		}
		if (n == 2) {
			std::vector<ll> ans;
			const ll mn = *min_element(a);
			while (a != b && *min_element(b) >= mn) {
				if (b.back() < b.front()) {
					ans.emplace_back(0);
					reverse(b);
				}
				if (*min_element(b) > mn) {
					const ll diff = b.back() - b.front();
					const ll cnt = (diff - 1) / b.front() + 1;
					ans.emplace_back(cnt);
					b.back() -= cnt * b.front();
				} else {
					const ll diff = *max_element(b) - *max_element(a);
					if (diff == 0) {
						if (a != b) {
							reverse(b);
							ans.emplace_back(0);
						}
						break;
					}
					const ll cnt = (diff - 1) / b.front() + 1;
					ans.emplace_back(cnt);
					b.back() -= cnt * b.front();
				}
			}
			if (a != b) {
				out << "IMPOSSIBLE" << std::endl;
				return;
			}
			out << ans_to_string(ans) << std::endl;
			return;
		}

		auto is_non_decreasing = [](const std::vector<ll>& a) {
			for (int i : range<int>(1, a.size())) {
				if (a[i] < a[i - 1]) {
					return false;
				}
			}
			return true;
		};

		std::vector<ll> ans;
		const ll mn = *min_element(a);
		while (*min_element(b) >= mn) {
			if (a == b) {
				out << ans_to_string(ans) << std::endl;
				return;
			}
			auto tmp = b;
			reverse(tmp);
			if (a == tmp) {
				ans.emplace_back(0);
				out << ans_to_string(ans) << std::endl;
				return;
			}
			if (!is_non_decreasing(b)) {
				b = tmp;
				if (!is_non_decreasing(b)) {
					out << "IMPOSSIBLE" << std::endl;
					return;
				}
				ans.emplace_back(0);
			}
			for (int i : downrange(n, 1)) {
				b[i] -= b[i - 1];
			}
			ans.emplace_back(1);
		}

		out << "IMPOSSIBLE" << std::endl;
	}


	FVkusnayaPechenka() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
