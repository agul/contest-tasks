#include "base/header.hpp"
#include "maths/maths.hpp"

class IncrementalHouseOfPancakes {
public:
	static constexpr bool kWriteCaseNumber = true;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll L, R;
		in >> L >> R;

		using Func = std::function<ll(const ll)>;

		Func count = [](const ll value) {
			return value * (value + 1) / 2;
		};

		Func count_odd = [](const ll value) {
			return sqr(value);
		};

		Func count_even = [](const ll value) {
			return value * (value + 1);
		};

		auto find_sum = [](const ll value, const Func& func, const ll prev) {
			return func(value) - func(prev);
		};

		auto solve = [&find_sum](const ll S, const Func& func, const ll prev) {
			ll L = prev;
			ll R = 2e9;
			while (R - L > 1) {
				ll md = (L + R) / 2;
				if (find_sum(md, func, prev) <= S) {
					L = md;
				} else {
					R = md;
				}
			}
			return L;
		};

		ll ans = 0;
		if (L > R) {
			ll diff = L - R;
			ans += solve(diff, count, 0);
			L -= count(ans);
		} else {
			ll diff = R - L;
			ans += solve(diff, count, 0);
			R -= count(ans);
		}

		auto update_ans = [&](ll& take_odd, ll& take_even, const ll last_odd, const ll last_even) {
			auto process = [&](ll& take, const Func& func, const ll prev_cnt) {
				const ll cnt = solve(take, func, prev_cnt);
				take -= find_sum(cnt, func, prev_cnt);
				ans += cnt - prev_cnt;
			};

			// debug(take_odd, take_even, last_odd, last_even);

			process(take_even, count_even, last_even / 2);
			process(take_odd, count_odd, (last_odd + 1) / 2);
		};

		// debug(ans, L, R);
		if (L < R) {
			if (ans & 1) {
				update_ans(L, R, ans, ans - 1);
			} else {
				update_ans(R, L, std::max<ll>(ans - 1, 0), ans);
			}
		} else {
			if (ans & 1) {
				update_ans(R, L, ans, ans - 1);
			} else {
				update_ans(L, R, std::max<ll>(ans - 1, 0), ans);
			}
		}
		out << ans << " " << L << " " << R << std::endl;
	}

	std::vector<ll> solve_slow(ll L, ll R) const {
		for (int i : range<ll>(1, L + R)) {
			if (i > L && i > R) {
				return std::vector<ll>({i - 1, L, R});
			}
			if (L < R) {
				R -= i;
			} else {
				L -= i;
			}
		}
		return std::vector<ll>({INF, L, R});
	}


	IncrementalHouseOfPancakes() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;
		for (int _ : range(testsCount)) {
			ll L, R;
			in >> L >> R;
			ll ans, l, r;
			auto jans = solve_slow(L, R);

			std::vector<ll> pans(3);
			std::string skip;
			out >> skip >> skip >> pans;

			if (jans != pans) {
				debug(_ + 1, jans, pans);
				return false;
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxValue = 100000;

		test << 1000 << std::endl;
		for (int i : range(1000)){
			test << Random::get(1, kMaxValue) << " " << Random::get(1, kMaxValue) << std::endl;
		}
	}

};
