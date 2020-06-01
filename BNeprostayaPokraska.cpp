#include "base/header.hpp"
#include "maths/prime.hpp"
#include "collections/value_compressor.hpp"

class BNeprostayaPokraska {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		SafeUnorderedMap<int, std::vector<int>> groups;
		IntegralValueCompressor<int> primes;
		std::vector<int> ans;
		ans.reserve(n);
		for (const auto& x : a) {
			const auto vec = get_prime_divisors_vector(x);
			const int min_prime = min_element(vec)->first;
			ans.emplace_back(primes[min_prime]);
		}
		out << primes.size() << std::endl;
		for (const auto& x : ans) {
			out << x + 1 << " ";
		}
		out << std::endl;
	}


	BNeprostayaPokraska() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
