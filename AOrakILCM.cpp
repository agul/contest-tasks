#include "base/header.hpp"
#include "maths/prime.hpp"
#include "maths/maths.hpp"

class AOrakILCM {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<ll> a(n);
		in >> a;

		SafeUnorderedMap<int, std::multiset<int>> cnt_for_prime_divs;
		std::vector<int> used_in_nums(kMaxn, 0);
		std::vector<std::vector<pli>> prime_divs;
		prime_divs.reserve(n);

		for (ll x : a) {
			const auto divs = get_prime_divisors_vector<ll, int>(x, min_prime_div);
			for (const auto& it : divs) {
				used_in_nums[it.first]++;
				cnt_for_prime_divs[it.first].emplace(it.second);
			}
			prime_divs.emplace_back(divs);
		}

		std::vector<int> all_but_one_prime_divs;
		for (int i : range(kMaxn)) {
			if (used_in_nums[i] >= n - 1) {
				all_but_one_prime_divs.emplace_back(i);
			}
		}

		auto get_min = [](const std::multiset<int>& set, const int cur_value = -1) {
			if (set.empty()) {
				return 0;
			}
			const auto it = set.cbegin();
			if (*it == cur_value) {
				if (set.size() == 1) {
					return 0;
				}
				return *std::next(it);
			}
			return *it;
		};

		std::vector<int> last_used(kMaxn, -1);
		std::vector<ll> lcms;
		for (int i : range(n)) {
			ll cur_lcm = 1;
			for (const auto& prime_div : prime_divs[i]) {
				int div;
				int cnt;
				std::tie(div, cnt) = prime_div;

				const int cur_div_min_cnt = get_min(cnt_for_prime_divs[div], cnt);
				cur_lcm *= binpow<ll>(div, std::max(cnt, cur_div_min_cnt));

				last_used[div] = i;
			}

			for (int div : all_but_one_prime_divs) {
				if (last_used[div] == i) {
					continue;
				}
				const int cur_div_min_cnt = get_min(cnt_for_prime_divs[div]);
				cur_lcm *= binpow<ll>(div, cur_div_min_cnt);
			}

			lcms.emplace_back(cur_lcm);

		}


		ll ans = lcms.front();
		for (ll x : lcms) {
			ans = gcd(ans, x);
		}
		out << ans << std::endl;
	}

	const int kMaxn = 222222;
	std::vector<ll> min_prime_div;

	AOrakILCM() {
		min_prime_div = min_prime_div_vector<ll>(kMaxn);
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};
