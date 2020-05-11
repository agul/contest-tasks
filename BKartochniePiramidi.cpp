#include "base/header.hpp"

class BKartochniePiramidi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		ll n;
		in >> n;
		int ans = 0;
		for (ll x : reversed(cnt)) {
			while (x <= n) {
				n -= x;
				++ans;
			}
		}
		out << ans << std::endl;
	}

	std::vector<ll> cnt;
	BKartochniePiramidi() {
		for (ll i : range(1, 100000)) {
			const ll cur = i * (i * 3 + 1) / 2;
			cnt.emplace_back(cur);
		}
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {}

};
