#include "base/header.hpp"
#include "maths/maths.hpp"

#define lll __int128

class DSostavlenieRezyume {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {

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

		auto calc_for_x = [](const ll a, const ll x) {
			return sqr(x) * 3 - x * 3 + 1 - a;
		};

		auto find_x = [&calc_for_x](const ll value, const ll limit) {
			ll L = 0;
			ll R = value + 1;
			while (R - L > 1) {
				const ll md = (L + R) / 2;
				if (calc_for_x(value, md) <= limit) {
					L = md;
				} else {
					R = md;
				}
			}
			return L;
		};

		auto calc_maximal_number_of_items = [&find_x, &a](const ll limit) {
			const int n = a.size();
			std::vector<ll> cur(n);
			for (int i : range(n)) {
				const ll value = a[i].first;
				cur[i] = find_x(value, limit);
			}
			return cur;
		};

		ll L = a.back().first;
		ll R = calc_for_x(L, L);
		while (R - L > 1) {
			const ll md = (L + R) / 2;
			const auto cur = calc_maximal_number_of_items(md);
			const ll sum = std::accumulate(all(cur), 0LL);
			if (sum < k) {
				L = md;
			} else {
				R = md;
			}
		}
		auto best = calc_maximal_number_of_items(R);

		auto cmp = [&calc_for_x, &best, &a](const int& lhs, const int& rhs) {
			const ll left_value = calc_for_x(a[lhs].first, best[lhs]);
			const ll right_value = calc_for_x(a[rhs].first, best[rhs]);
			return left_value > right_value || (left_value == right_value && lhs < rhs);
		};

		std::set<int, decltype(cmp)> items(cmp);
		for (int i : range(n)) {
			if (best[i] > 0) {
				items.emplace(i);
			}
		}

		ll sum = std::accumulate(all(best), 0LL);
		while (sum > k) {
			const int index = *items.begin();
			items.erase(index);
			best[index]--;
			--sum;
			if (best[index] > 0) {
				items.emplace(index);
			}
		}

		std::vector<ll> ans(n);
		for (int i : range(n)) {
			ans[a[i].second] = best[i];
		}

		for (ll x : ans) {
			out << x << " ";
		}
		out << std::endl;
	}

	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}
};
