#include "base/header.hpp"
#include "maths/rational.hpp"

class CSmeshivaemVodu {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	using Ratio = Rational<ll>;

	const ld kEps = 1e-16;

	void solve(std::istream& in, std::ostream& out) {
		int h, c, t;
		in >> h >> c >> t;
		// out << solve_ternary(h, c, t) << std::endl;
		out << solve_equation(h, c, t) << std::endl;
	}

	int solve_equation(const int h, const int c, const int t) {
		if (2 * t <= h + c) {
			return 2;
		}

		const int a = t - h;
		const int b = h + c - 2 * t;
		const int L = std::max(0, a / b - 10);
		const int R = a / b + 10;

		auto check_ratio = [t, h, c](const ll hot) {
			return std::abs(Ratio{(hot + 1) * h + hot * c, 2 * hot + 1} - Ratio{t});
		};

		auto check = [t, h, c](const ld hot) {
			return std::abs(((hot + 1) * h + hot * c) / (2 * hot + 1) - t);
		};

		auto best = check(L);
		int ans = L;
		for (int i : inclusiveRange(L, R)) {
			const auto cur_value = check(i);
			if (best > cur_value + kEps) {
				best = cur_value;
				ans = i;
			}
		}
		return ans * 2 + 1;
	}

	int solve_ternary(const int h, const int c, const int t) {
		if (2 * t <= h + c) {
			return 2;
		}

		ll L = 0;
		ll R = 1e12;

		auto check = [t, h, c](const ll hot) {
			return (Ratio{(hot + 1) * h + hot * c, 2 * hot + 1} - Ratio{t}).abs();
		};

		while (R - L > 2) {
			ll diff = (R - L);
			ll m1 = L + diff / 3;
			ll m2 = R - diff / 3;
			if (check(m1) < check(m2)) {
				R = m2;
			} else {
				L = m1;
			}
		}

		Ratio best = check(0);
		ll ans = 0;
		for (ll i : range(std::max(L - 10, 0LL), R + 10)) {
			const Ratio cur_value = check(i);
			if (best > cur_value) {
				best = cur_value;
				ans = i;
			}
		}
		return ans * 2 + 1;
	}

	int solve_stupid(const double hot, const double cold, const double temp) {
		if (temp * 2 <= hot + cold) {
			return 2;
		}

		double best_diff = INF;
		double prev_diff = INF;
		int jans = 1;
		int cnt = 0;

		for (int i : range(1, 100000)) {
			const double cur_temp = (hot * i + cold * (i - 1)) / (2 * i - 1);
			const double cur_diff = std::abs(cur_temp - temp);
			if (cur_diff + EPS < best_diff) {
				best_diff = cur_diff;
				jans = 2 * i - 1;
			} else {
				if (cur_diff > prev_diff + EPS) {
					++cnt;
					if (cnt == 10) {
						break;
					}
				} else {
					cnt = 0;
					prev_diff = cur_diff;
				}
			}
		}
		return jans;
	}


	CSmeshivaemVodu() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;

		/* double cold, hot, temp;
		in >> hot >> cold >> temp;

		int pans;
		out >> pans;

		const int jans = solve_stupid(hot, cold, temp);
		if (pans != jans) {
			debug(jans, pans);
			return false;
		} */

		for (int test_id : range(testsCount)) {
			int h, c, t;
			in >> h >> c >> t;
			int pans, jans;
			out >> pans;
			jury >> jans;
			if (pans != jans) {
				debug("FAIL", test_id);
				debug(h, c, t);
				debug(pans, jans);
				return false;
			}
		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 1000000;

		const int cold = Random::get(1, kMaxn);
		const int hot = Random::get(cold, kMaxn);
		const int temp = Random::get(cold, hot);
		test << 1 << std::endl;
		test << hot << " " << cold << " " << temp << std::endl;
	}

};
