#include "base/header.hpp"
#include "maths/prime.hpp"

class FUgadatKolichestvoDelitelei {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	static constexpr int kMaxPrime = 647;

	void solve(std::istream& in, std::ostream& out) {
		std::vector<ll> divs;
		ll cur = 1;
		for (int x : primes) {
			if (x > 100 && cur >= 1e16 || x > 10 && cur >= 1e17 || cur * x >= 1e18) {
				divs.emplace_back(cur);
				cur = 1;
			}
			cur *= x;
		}
		divs.emplace_back(cur);
		debug(divs.size());

		std::vector<ll> gcds;
		for (const ll div : divs) {
			out << "? " << div << std::endl;
			ll cur_gcd;
			in >> cur_gcd;
			gcds.emplace_back(cur_gcd);
		}

		std::vector<pll> candidates;
		for (int x : primes) {
			bool any = false;
			for (const ll gcd : gcds) {
				if (gcd % x == 0) {
					any = true;
				}
			}
			if (!any) {
				continue;
			}
			ll cur = 1;
			while (cur * x < 1e9) {
				cur *= x;
			}
			candidates.emplace_back(cur, x);
		}

		ll ans = 1;
		ll number = 1;
		auto process = [&number, &ans](ll gcd, const ll prime) {
			debug(gcd);
			int cnt = 0;
			while (gcd > 1 && gcd % prime == 0) {
				gcd /= prime;
				++cnt;
			}
			debug(prime, cnt);
			ans *= (cnt + 1);
		};

		for (int i = 0; i < candidates.size(); i += 2) {
			ll cur = candidates[i].first;
			if (i + 1 < candidates.size()) {
				cur *= candidates[i + 1].first;
			}
			out << "? " << cur << std::endl;
			ll value;
			in >> value;
			number *= value;
			process(value, candidates[i].second);
			if (i + 1 < candidates.size()) {
				process(value, candidates[i + 1].second);
			}
		}

		out << "! " << std::max(ans + 7, ans * 2) << std::endl;
	}


	std::vector<int> primes;
	FUgadatKolichestvoDelitelei() {
		primes = primes_vector<int>(kMaxPrime);
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
