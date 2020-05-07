#include "base/header.hpp"
#include "maths/maths.hpp"

class EllysDifferentPrimes {
public:
	int getClosest(int N) {
		std::vector<int> primes;
		primes_vector(50123470, &primes);

		std::vector<int> different_primes;
		for (int x : primes) {
			std::vector<bool> used(10);
			int cur = x;
			bool ok = true;
			while (cur > 0 && ok) {
				int digit = cur % 10;
				ok &= !used[digit];
				used[digit] = true;
				cur /= 10;
			}
			if (ok) {
				different_primes.emplace_back(x);
			}
		}

		int best = different_primes.front();
		for (int i : different_primes) {
			if (abs(i - N) < abs(best - N)) {
				best = i;
			}
		}
		return best;
	}
};

class TCO20_1B_hard {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		EllysDifferentPrimes solution;
		out << solution.getClosest(n) << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
