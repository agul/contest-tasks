#include "base/header.hpp"
#include "maths/prime.hpp"

#define lll __int128

class DSostavlenieRezyume {
public:
	void solve(std::istream& in, std::ostream& out) {
		out << random_big_prime() << std::endl;
		for (int i : range(5)) {
			out << random_prime(1, 100) << " ";
		}
		out << std::endl;

		return;

		int n;
		ll k;
		in >> n >> k;
		std::vector<pli> a;
		for (int i : range(n)) {
			ll x;
			in >> x;
			a.emplace_back(x, i);
		}
		sort(a);

		const lll max_value = a.back().first;
		lll R = max_value;
		lll L = max_value * (max_value - max_value * max_value);

		auto solve_for_limit = [&a](const lll limit) {
			std::vector<ll> res;
			for (const auto& it : a) {
				const ll value = it.first;
				ll L = 0;
				ll R = value + 1;
				while (R - L > 1) {
					const lll md = (L + R) / 2;
					if (md * md * 3 - md * 3 + (limit + 1 - value) <= 0) {
						L = md;
					} else {
						R = md;
					}
				}
				res.emplace_back(L);
			}
			return res;
		};


		while (R - L > 1) {
			const lll limit = (L + R) / 2;
			const auto cur_vec = solve_for_limit(limit);
			const lll cur_sum = std::accumulate(all(cur_vec), (lll)0);
			// debug(k, cur_sum, limit);
			if (cur_sum >= k) {
				L = limit;
			} else {
				R = limit;
			}
		}

		const auto cur_vec = solve_for_limit(L);
		std::vector<ll> ans(n);
		std::set<pli> items;
		ll cur_sum = 0;
		for (int i : range(n)) {
			ans[a[i].second] = cur_vec[i];
			items.emplace(-cur_vec[i], i);
			cur_sum += cur_vec[i];
		}

		debug(cur_sum, (ll)L , (ll)R, (ll)max_value);
		if (cur_sum < k) {
			out << cur_sum << " " << (ll)L << " " << (ll)R << " " << (ll)max_value << std::endl;
			return;
		}

		while (cur_sum > k) {
			auto it = items.begin();
			ll value;
			int index;
			std::tie(value, index) = *it;
			items.erase(it);
			--ans[a[index].second];
			items.emplace(value + 1, index);
			--cur_sum;
		}


		for (ll x : ans) {
			out << x << " ";
		}
		out << std::endl;
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
