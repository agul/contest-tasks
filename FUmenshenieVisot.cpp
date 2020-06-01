#include "base/header.hpp"

class FUmenshenieVisot {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	ll check(const std::vector<std::vector<ll>>& a, const int n, const int m, const ll height) const {
		if (a[0][0] < height) {
			return LINF;
		}
		auto dp = make_vector<ll>(n + 1, m + 1, LINF);
		dp[0][0] = a[0][0] - height;
		for (int i : range(n)) {
			for (int j : range(m)) {
				int len = i + j + 1;
				const ll new_height = height + len;
				if (i + 1 < n && new_height <= a[i + 1][j]) {
					const ll diff = a[i + 1][j] - new_height;
					umin(dp[i + 1][j], dp[i][j] + diff);
				}
				if (j + 1 < m && new_height <= a[i][j + 1]) {
					const ll diff = a[i][j + 1] - new_height;
					umin(dp[i][j + 1], dp[i][j] + diff);
				}
				// debug(i, j, dp[i + 1][j], dp[i][j + 1]);
			}
		}
		return dp[n - 1][m - 1];
	}

	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		auto a = make_vector<ll>(n, m, 0);
		in >> a;

		for (int i : range(-10, 10)) {
			out << i << " " << check(a, n, m, i) << std::endl;
		}
		return;

		ll R = a[0][0];
		ll L = -static_cast<ll>(1e18);
		while (R - L > 2) {
			const ll diff = (R - L) / 3;
			const ll m1 = L + diff;
			const ll m2 = R - diff;

			if (check(a, n, m, m1) > check(a, n, m, m2)) {
				L = m1;
			}
			else {
				R = m2;
			}
		}
		ll ans = LINF;
		for (ll i : inclusiveRange(L, R)) {
			const ll value = check(a, n, m, i);
			umin(ans, value);
			// debug(i, value);
		}
		out << ans << std::endl;
	}


	FUmenshenieVisot() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;

		int n, m;
		in >> n >> m;
		auto a = make_vector<ll>(n, m, 0);
		in >> a;

		ll jans = LINF;
		for (int i : range(n)) {
			for (int j : range(m)) {
				umin(jans, check(a, n, m, a[i][j] - i - j));
			}
		}

		ll pans;
		out >> pans;

		if (pans != jans) {
			debug(pans, jans);
			return false;
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 6;
		const int kMinValue = 1;
		const int kMaxValue = 10;

		const int n = Random::get(1, kMaxn);
		const int m = Random::get(1, kMaxn);
		auto a = make_vector<ll>(n, m, 0);
		for (int i : range(n)) {
			for (int j : range(m)) {
				a[i][j] = Random::get(kMinValue, kMaxValue);
			}
		}

		test << 1 << std::endl;
		test << n << " " << m << std::endl;
		for (int i : range(n)) {
			for (int j : range(m)) {
				test << a[i][j] << " ";
			}
			test << std::endl;
		}
	}

};
