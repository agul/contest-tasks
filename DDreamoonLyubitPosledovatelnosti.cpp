#include "../algolib/cpplib/base/header.hpp"
#include "../algolib/cpplib/maths/maths.hpp"

class DDreamoonLyubitPosledovatelnosti {
public:
	void solve(std::istream& in, std::ostream& out) {
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n, mod;
			in >> n >> mod;
			if (n == 1) {
				out << 1 % mod << std::endl;
				continue;
			}
			if (n == 2) {
				out << 3 % mod << std::endl;
				continue;
			}

			ll primes_sum = 1;
			ll cur_value = 2 % mod;
			for (int prime_idx : range(1, (int)primes.size())) {
				const int prime = primes[prime_idx];
				const ll diff = prime - 1;
				if (primes_sum + diff >= n) {
					break;
				}
				primes_sum += diff;
				cur_value = cur_value * prime % mod;
				// std::cout << "RUN " << prime << " " << primes_sum << " " << cur_value << std::endl;
			}
			const ll value = n - primes_sum + 1;
			// std::cout << "END " << primes_sum << " " << cur_value << " " << value << std::endl;
			cur_value = cur_value * value % mod;
			out << (cur_value - 1 + mod) % mod << std::endl;
		}
	}



	const int kMaxPrime = 166666;

	DDreamoonLyubitPosledovatelnosti() {
		primes_vector(kMaxPrime, &primes);
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	std::vector<int> primes;
	size_t test_id_ = 0;
};
