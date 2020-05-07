#include "base/header.hpp"

class CF1348_E {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		auto a = make_vector<pll>(n, pll{0, 0});
		in >> a;

		ll sum_red = 0;
		ll sum_blue = 0;
		ll greedy_ans = 0;
		ll rem_red = 0;
		ll rem_blue = 0;
		for (const auto& it : a) {
			sum_red += it.X;
			sum_blue += it.Y;

			greedy_ans += (it.X + it.Y) / k;
			const ll rem = (it.X + it.Y) % k;
			if (rem <= it.X) {
				rem_red += rem;
			}
			if (rem <= it.Y) {
				rem_blue += rem;
			}
		}
		if (rem_red >= k || rem_blue >= k) {
			++greedy_ans;
		}

		ll ans = (sum_red / k) + (sum_blue / k);
		debug(sum_red, sum_blue);
		debug(a);
		sum_red %= k;
		// sum_blue %= k;

		if (sum_red > 0) {
			debug(sum_red, sum_blue);
			for (const auto& it : a) {
				for (int rem : inclusiveRange(1LL, sum_red)) {
					debug(rem, k - rem);
					if (rem <= it.X && k - rem <= it.Y && k - rem <= sum_blue) {
						out << std::max(greedy_ans, ans + 1) << std::endl;
						return;
					}
				}
			}
		}

		out << std::max(greedy_ans, ans) << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
