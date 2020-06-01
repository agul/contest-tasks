#include "base/header.hpp"

class DDevuIBratishka {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	static ll calc(const std::vector<ll>& a, const std::vector<ll>& b, const ll value) {
		ll ans = 0;
		for (ll x : a) {
			ans += std::max(0LL, value - x);
		}
		for (ll x : b) {
			ans += std::max(0LL, x - value);
		}
		return ans;
	};

	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		std::vector<ll> a(n);
		std::vector<ll> b(m);
		in >> a >> b;

		ll L = *min_element(a);
		ll R = std::max(L, *max_element(b)) + 1;

		while (R - L > 2) {
			const ll diff = (R - L) / 3;
			const ll m1 = L + diff;
			const ll m2 = R - diff;
			if (calc(a, b, m1) < calc(a, b, m2)) {
				R = m2;
			} else {
				L = m1;
			}
		}
		ll ans = calc(a, b, L);
		for (ll i : range(L, R + 1)) {
			umin(ans, calc(a, b, i));
		}
		out << ans << std::endl;
	}


	DDevuIBratishka() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n, m;
		in >> n >> m;
		std::vector<ll> a(n);
		std::vector<ll> b(m);
		in >> a >> b;

		ll L = *min_element(a);
		ll R = std::max(L, *max_element(b));

		ll jans = calc(a, b, L);
		for (ll i : range(L, R + 1)) {
			umin(jans, calc(a, b, i));
		}

		ll pans;
		out >> pans;

		if (jans != pans) {
			debug(jans, pans);
			return false;
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 100;
		const int kMaxValue = 100;

		const int n = Random::get(1, kMaxn);
		const int m = Random::get(1, kMaxValue);

		std::vector<ll> a(n);
		std::vector<ll> b(m);

		for (int i : range(n)) {
			a[i] = Random::get(1, kMaxValue);
		}
		for (int i : range(m)) {
			b[i] = Random::get(1, kMaxValue);
		}

		test << n << " " << m << std::endl;
		for (ll x : a) {
			test << x << " ";
		}
		test << std::endl;
		for (ll x : b) {
			test << x << " ";
		}
		test << std::endl;
	}

};
