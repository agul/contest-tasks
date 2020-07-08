#include "base/header.hpp"
#include "maths/mod_int.hpp"
#include "maths/bits.hpp"

class EMultiplication4 {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<int>;

	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		std::vector<ll> negative;
		std::vector<ll> positive;
		int zeroes = 0;
		for (int i : range(n)) {
			ll x;
			in >> x;
			if (x == 0) {
				++zeroes;
				continue;
			}
			if (x < 0) {
				negative.emplace_back(std::abs(x));
				continue;
			}
			if (x > 0) {
				positive.emplace_back(x);
				continue;
			}
			assert(false);
		}

		const int negative_count = negative.size();
		const int positive_count = positive.size();

		if (negative_count + positive_count < k) {
			out << 0 << std::endl;
			return;
		}

		if (negative_count + positive_count == k) {
			if (negative_count % 2 == 1) {
				if (zeroes > 0) {
					out << 0 << std::endl;
					return;
				}
				Int ans = 1;
				for (ll x : positive) {
					ans *= x;
				}
				for (ll x : negative) {
					ans *= x;
				}
				ans = -ans;
				out << ans << std::endl;
				return;
			}
		}

		sort(negative, std::greater<>());
		sort(positive, std::greater<>());

		if (positive_count == 0) {
			Int ans = 1;
			if (k % 2 == 1) {
				if (zeroes > 0) {
					out << 0 << std::endl;
					return;
				}
				reverse(negative);
				ans = -ans;
			}
			for (int i : range(k)) {
				ans *= negative[i];
			}
			out << ans << std::endl;
			return;
		}


		ld cur_log = 0;
		int pos_index = 0;
		if (k > positive_count) {
			if ((k - positive_count) % 2 == 1) {
				pos_index = positive_count - 1;
			} else {
				pos_index = positive_count;
			}
		} else {
			pos_index = k;
		}
		int neg_index = k - pos_index;

		Int ans = 1;
		for (int i : range(pos_index)) {
			ans *= positive[i];
		}
		for (int j : range(neg_index)) {
			ans *= negative[j];
		}

		for (int neg_cnt = neg_index + 2; neg_cnt <= negative_count && neg_cnt <= k; neg_cnt += 2) {
			const ll last_pos = positive[pos_index - 1] * positive[pos_index - 2];
			const ll next_neg = negative[neg_index] * negative[neg_index + 1];

			if (next_neg > last_pos) {
				ans *= Int::from_integer(last_pos).inverse();
				ans *= Int::from_integer(next_neg);
				pos_index -= 2;
				neg_index += 2;
			} else {
				break;
			}

		}


		out << ans << std::endl;
	}


	EMultiplication4() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n, k;
		in >> n >> k;
		std::vector<ll> a(n);
		in >> a;

		ll best = -LINF;
		for (int mask : range(1 << n)) {
			if (popcount(mask) != k) {
				continue;
			}
			ll ans = 1;
			for (int i : range(n)) {
				if (test_bit(mask, i)) {
					ans *= a[i];
				}
			}
			umax(best, ans);
		}

		Int pans;
		out >> pans;

		const Int jans = Int::from_integer(best);

		if (pans != jans) {
			debug(pans, jans, best);
			return false;
		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 20;
		const int kMaxm = 10;
		const int kMinm = -10;

		const int n = Random::get(1, kMaxn);
		const int k = Random::get(1, n);
		test << n << " " << k << std::endl;
		for (int i : range(n)) {
			test << Random::get(kMinm, kMaxm) << " ";
		}
		test << std::endl;
	}

};
