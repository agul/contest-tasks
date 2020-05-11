#include "base/header.hpp"
#include "maths/prime.hpp"

class CMaikIPena {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, q;
		in >> n >> q;
		std::vector<int> a(n);
		in >> a;

		std::vector<std::vector<int>> divisors(n);
		for (int i : range(n)) {
			const int x = a[i];
			const auto divs = divisors_vector(x);
			auto& cur_divisors = divisors[i];
			cur_divisors.reserve(divs.size());
			for (int div : divs) {
				if (good_divisors_set.find(div) != good_divisors_set.cend()) {
					cur_divisors.emplace_back(div);
				}
			}
		}

		std::vector<int> divisors_cnt(kMaxn, 0);
		std::vector<bool> used(n, false);

		auto shelf = [&divisors_cnt, &divisors](const int index, const int delta) {
			for (int div : divisors[index]) {
				divisors_cnt[div] += delta;
			}
		};

		auto count = [&divisors_cnt, &divisors, this](const int index) {
			ll ans = 0;
			for (int div : divisors[index]) {
				ans += divisors_cnt[div] * div_multiplier[div];
			}
			return ans;
		};

		ll ans = 0;
		ll shelf_size = 0;
		for (int _ : range(q)) {
			debug(divisors_cnt);
			int x;
			in >> x;
			--x;
			bool dry_run = false;
			int multiplier = 1;
			if (used[x]) {
				shelf(x, -1);
				dry_run = true;
				multiplier = -1;
				used[x] = false;
				--shelf_size;
			}
			const ll cur_value = shelf_size - count(x);
			if (!dry_run) {
				shelf(x, 1);
				used[x] = true;
				++shelf_size;
			}
			ans += cur_value * multiplier;
			out << ans << std::endl;
		}
	}

	const int kMaxn = 555555;
	std::vector<int> min_prime_div;
	SafeUnorderedSet<int> good_divisors_set;
	std::vector<int> div_multiplier;
	CMaikIPena() {
		min_prime_div = min_prime_div_vector<int>(kMaxn);
		div_multiplier.assign(kMaxn, 0);
		for (int i : range(2, kMaxn)) {
			int cur = i;
			int last = -1;
			bool ok = true;
			int cnt = 0;
			while (cur > 1 && ok) {
				const int div = min_prime_div[cur];
				ok &= (last != div);
				last = div;
				cur /= div;
				++cnt;
			}
			if (ok) {
				good_divisors_set.emplace(i);
				div_multiplier[i] = (cnt % 2 == 1 ? 1 : -1);
			}
		}
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {}

};
