#include "base/header.hpp"
#include "maths/mod_int.hpp"

class BDuffNaPlyazhe {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<ll, 1000000007>;

	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		ll l;
		in >> n >> l >> k;
		std::vector<pii> a;
		for (int i : range(n)) {
			int x;
			in >> x;
			a.emplace_back(x, i);
		}
		sort(a);

		const ll full = l / n;
		const ll rem = l % n;

		auto dp = make_vector<Int>(n, k + 1, 0);
		auto last = make_vector<Int>(n, k + 1, 0);
		for (int i : range(n)) {
			dp[i][1] = 1;
			if (a[i].second < rem) {
				last[i][1] = 1;
			}
		}

		for (int j : range(2, k + 1)) {
			Int sum = 0;
			Int sum_last = 0;
			int index = n - 1;
			for (int i : downrange(n)) {
				while (index >= 0 && a[index].first >= a[i].first) {
					sum += dp[index][j - 1];
					sum_last += last[index][j - 1];
					--index;
				}
				dp[i][j] = sum;
				last[i][j] = sum_last;
			}
		}

		for (int i : range(n)) {
			// debug(i, dp[i]);
		}

		for (int i : range(n)) {
			// debug(i, last[i]);
		}

		Int ans = 0;
		for (int i : range(n)) {
			for (int j : range(1, k + 1)) {
				if (j <= full + 1) {
					ans += last[i][j];
				}
				ans += dp[i][j] * Int::from_integer(std::max(0LL, (full - j + 1)));
			}
		}

		out << ans << std::endl;
	}


	BDuffNaPlyazhe() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n, l, k;
		in >> n >> l >> k;
		std::vector<int> b(n);
		in >> b;

		std::vector<int> a;
		a.reserve(l);
		for (int i : range(l)) {
			a.emplace_back(b[i % n]);
		}

		auto dp = make_vector<Int>(l, k + 1, 0);
		for (int i : range(l)) {
			dp[i][1] = 1;
		}

		Int jans = l;
		for (int i : downrange(l)) {
			const int block_id = i / n;
			const int next_block_start = std::min(l, (block_id + 1) * n);
			const int next_block_end = std::min(l, (block_id + 2) * n);
			const int cur_value = a[i];
			for (int j : range(2, k + 1)) {
				for (int x : range(next_block_start, next_block_end)) {
					if (a[x] >= a[i]) {
						dp[i][j] += dp[x][j - 1];
					}
				}
				jans += dp[i][j];
				// debug(i, j, dp[i][j]);
			}
		}

		Int pans;
		out >> pans;
		if (pans != jans) {
			debug(pans, jans);
			return false;
		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
#ifdef USE_JNGEN
		const int kMaxn = 100;
		const int kMaxl = 100;
		const int kMaxk = 1000;
		const int kMaxValue = 100000;

		const int n = Random::get(1, kMaxn);
		const int l = Random::get(1, kMaxl);
		const int k = Random::get(1, kMaxk);

		auto a = jngen::Array::random(n, 1, kMaxValue);
		test << n << " " << l << " " << k << std::endl;
		test << a << std::endl;
#endif
	}

};
