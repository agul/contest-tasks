#include "base/header.hpp"
#include "maths/mod_int.hpp"

class DGukiZIDvoichnieOperatsii {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {

		auto test = [](const uint64_t mask, const int i) {
			return (mask & (1ULL << i)) > 0;
		};

		/*
		for (int n : range(1, 10)) {
			int cnt = 0;
			for (int mask : range(1 << n)) {
				for (int i : range(1, n)) {
					if (test(mask, i) && test(mask, i - 1)) {
						++cnt;
						break;
					}
				}
			}
			out << n << " " << cnt << " " << (1 << n) - cnt << std::endl;
		}
		return;
		*/

		ll n, k, l, mod;
		in >> n >> k >> l >> mod;
		if (l < 60 && (1ULL << l) <= k) {
			out << 0 << std::endl;
			return;
		}

		ll ans = 1 % mod;
		const ll two_n = binpow(2LL, n, mod);
		const ll nth_fib = get_nth_fib(n + 1, mod);


		const ll cur = (two_n - nth_fib + mod) % mod;
		// debug(nth_fib);
		// debug(two_n);
		// debug(cur);

		for (int bit : range(l)) {
			if (test(k, bit)) {
				mul_mod(ans, cur, mod);
			} else {
				mul_mod(ans, nth_fib, mod);
			}
		}
		out << ans << std::endl;
	}

	using Matrix = std::vector<std::vector<ll>>;

	Matrix multiply(const Matrix& lhs, const Matrix& rhs, const ll mod) const {
		Matrix result = {{0, 0}, {0, 0}};
		for (size_t i = 0; i < 2; i++) {
			for (size_t k = 0; k < 2; k++) {
				for (size_t j = 0; j < 2; j++) {
					ll value = lhs[i][j];
					mul_mod(value, rhs[j][k], mod);
					add_mod(result[i][k], value, mod);
				}
			}
		}
		return result;
	}

	ll get_nth_fib(ll b, const ll mod) {
		Matrix fib = {{1 % mod, 0}, {0, 1 % mod}};
		Matrix a = {{0, 1 % mod}, {1 % mod, 1 % mod}};
		while (b != 0) {
			if ((b & 1) != 0) {
				fib = multiply(fib, a, mod);
			}
			a = multiply(a, a, mod);
			b >>= 1;
		}
		ll ans = fib[0][0];
		add_mod(ans, fib[1][0], mod);
		return ans;
	}

	DGukiZIDvoichnieOperatsii() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		ll n, k, l, mod;
		in >> n >> k >> l >> mod;

		ll pans;
		out >> pans;

		using Int = ModInt<int>;

		Int jans = 0;
		if ((1LL << l) <= k) {
			if (jans != pans) {
				debug(jans, pans);
				return false;
			}
			return true;
		}

		Int a = 1;
		Int b = 1;
		for (int i : range(n)) {
			Int t = a + b;
			a = b;
			b = t;
		}


		Int pow2 = binpow(Int(2), n);
		// debug(b);
		// debug(pow2);
		// debug(pow2 - b);

		Int ans = 1;
		for (int i : range(l)) {
			if (k & (1LL << i)) {
				ans *= (pow2 - b);
			} else {
				ans *= b;
			}
		}

		jans = Int(ans.value() % mod);

		if (jans != pans) {
			debug(jans, pans);
			return false;
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 3500;
		const int kMaxL = 50;

		const int n = Random::get(2, kMaxn);
		const ll k = Random::get(1LL, 1LL << kMaxL);
		const int l = Random::get(0, kMaxL);
		const int mod = 1000000007;

		test << n << " " << k << " " << l << " " << mod << std::endl;
	}

};
