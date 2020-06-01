#include "base/header.hpp"

class DNaviki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		ll A, cf, cm, m;
		in >> n >> A >> cf >> cm >> m;
		std::vector<pii> a;
		for (int i : range(n)) {
			int x;
			in >> x;
			a.emplace_back(x, i);
		}
		sort(a);

		std::vector<ll> prefs = {0};
		for (int i : range(1, n)) {
			prefs.emplace_back(prefs.back() + (a[i].first - a[i - 1].first) * i);
		}

		ll ans = 0;
		ll min_force = 0;
		ll cnt_max = 0;
		ll cur_sum_to_max = 0;

		auto update_ans = [&ans, &min_force, &cnt_max, cf, cm](ll cur_min_force, ll cur_cnt_max) {
			const ll cur_value = cf * cur_cnt_max + cm * cur_min_force;
			if (umax(ans, cur_value)) {
				cnt_max = cur_cnt_max;
				min_force = cur_min_force;
				return true;
			}
			return false;
		};

		for (int cnt : inclusiveRange(0, n)) {
			if (cnt > 0) {
				cur_sum_to_max += A - a[n - cnt].first;
			}
			const ll left = m - cur_sum_to_max;
			if (left < 0) {
				break;
			}
			if (cnt == n) {
				update_ans(A, n);
				break;
			}
			auto it = upper_bound(prefs.begin(), prefs.begin() + n - cnt, left) - 1;
			const ll remaining_add = left - *it;
			const int equal_skills_cnt = it - prefs.cbegin() + 1;

			const ll cur_min_force = std::min(A, a[equal_skills_cnt - 1].first + remaining_add / equal_skills_cnt);
			update_ans(cur_min_force, cnt);
		}

		// debug(ans, cnt_max, min_force);

		std::vector<ll> vals(n, -1);
		for (int i : range(cnt_max)) {
			vals[a[n - 1 - i].second] = A;
		}
		for (int i : range(n - cnt_max)) {
			vals[a[i].second] = std::max<ll>(min_force, a[i].first);
		}

		out << ans << std::endl;
		for (ll x : vals) {
			out << x << " ";
		}
		out << std::endl;
	}


	DNaviki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n;
		ll A, cf, cm, m;
		in >> n >> A >> cf >> cm >> m;

		std::vector<ll> pvalues(n);
		ll pans;
		out >> pans >> pvalues;

		const ll p_min_force = *min_element(pvalues);
		const ll p_cnt_max = std::count(all(pvalues), A);
		const ll p_total_force = p_min_force * cm + p_cnt_max * cf;

		if (pans != p_total_force) {
			debug(pans, p_total_force);
			return false;
		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 1000;
		const ll kMaxValue = 10000;
		const ll kMaxCoef = 1000;

		const int n = Random::get(1, kMaxn);
		const ll A = Random::get<ll>(1, kMaxValue);
		const ll cf = Random::get<ll>(0, kMaxCoef);
		const ll cm = Random::get<ll>(0, kMaxCoef);
		const ll m = Random::get<ll>(0, kMaxValue);

		test << n << " " << A << " " << cf << " " << cm << " " << m << std::endl;
		for (int i : range(n)) {
			test << Random::get(0LL, A) << " ";
		}
		test << std::endl;
	}

};
