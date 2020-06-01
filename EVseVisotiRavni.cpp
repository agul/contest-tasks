#include "base/header.hpp"
#include "maths/mod_int.hpp"

class EVseVisotiRavni {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<ll, 998244353>;

	void solve(std::istream& in, std::ostream& out) {
		ll n, m, L, R;
		in >> n >> m >> L >> R;

		auto count_odd = [](const ll n) {
			return (n + 1) / 2;
		};

		auto count_even = [](const ll n) {
			return n / 2;
		};

		ll odds = count_odd(R) - count_odd(L - 1);
		ll evens = count_even(R) - count_even(L - 1);
		ll total = R - L + 1;

		ll cells = n * m;
		Int ans = binpow(Int{total}, cells);
		if (cells % 2 == 0) {
			Int rem = ans;
			rem -= binpow(Int{evens - odds}, cells);
			rem *= Int{2}.inverse();
			ans -= rem;
		}
		out << ans << std::endl;
	}


	EVseVisotiRavni() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
