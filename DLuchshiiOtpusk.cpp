#include "base/header.hpp"

class DLuchshiiOtpusk {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		ll x;
		in >> n >> x;
		std::vector<ll> a(n);
		in >> a;

		a.insert(a.end(), all(a));

		std::vector<ll> prefs = {0};
		prefs.reserve(2 * n + 1);
		for (ll x : a) {
			prefs.emplace_back(prefs.back() + x);
		}

		auto find_sum = [](const ll n) {
			return n * (n + 1) / 2;
		};

		auto calculate_value = [&find_sum](const ll start, const ll finish) {
			return find_sum(finish) - find_sum(start - 1);
		};

		std::vector<ll> month_sum;
		month_sum.reserve(n * 2);
		for (ll x : a) {
			month_sum.emplace_back(find_sum(x));
		}

		std::vector<ll> pref_month_sums = {0};
		pref_month_sums.reserve(2 * n + 1);
		for (ll x : month_sum) {
			pref_month_sums.emplace_back(pref_month_sums.back() + x);
		}

		auto get_ans_for_months = [&pref_month_sums, n](const int x, const int y) {
			if (x <= 0 || y > 2 * n || x > y) {
				return 0LL;
			}
			return pref_month_sums[y] - pref_month_sums[x - 1];
		};

		auto find_month = [&prefs](const ll day) {
			const int index = upper_bound(prefs, day - 1) - prefs.begin() - 1;
			return index + 1;
		};

		auto calc_from_start = [&prefs, n, x, &get_ans_for_months, &find_month, &calculate_value, &a](const ll starting_day) {

			const ll ending_day = starting_day + x - 1;

			const int starting_month = find_month(starting_day);
			const int ending_month = find_month(ending_day);


			ll ans = get_ans_for_months(starting_month + 1, ending_month - 1);
			// debug(starting_day, ending_day, starting_month, ending_month, ans);
			if (starting_month == ending_month) {
				ans += calculate_value(starting_day - prefs[starting_month - 1], ending_day - prefs[ending_month - 1]);
			} else {
				ans += calculate_value(starting_day - prefs[starting_month - 1], a[starting_month - 1]);
				ans += calculate_value(1, ending_day - prefs[ending_month - 1]);
			}

			// debug(starting_day, ans);
			return ans;
		};

		ll ans = 0;
		for (int i : range(2 * n + 1)) {
			const ll day = prefs[i] + 1;
			if (day <= prefs[n]) {
				umax(ans, calc_from_start(day));
			}
		}
		// debug("---");

		for (int i : range(2 * n + 1)) {
			const ll day = prefs[i] - x + 1;
			if (day > 0) {
				umax(ans, calc_from_start(day));
			}
		}
		out << ans << std::endl;

	}


	DLuchshiiOtpusk() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
