#include "base/header.hpp"

class BSummaSlagaemikhOdinakovoiChetnosti {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			ll n, k;
			in >> n >> k;


			int min_value = 1;
			if (k % 2 == 1 && n % 2 == 0) {
				min_value = 2;
			}


			if ((n % 2 == 1 && k % 2 == 0) || n < k * min_value) {
				out << "NO" << std::endl;
				continue;
			}

			out << "YES" << std::endl;
			for (int i : range(k - 1)) {
				out << min_value << " ";
			}
			out << n - (k - 1) * min_value << std::endl;

		}
	}

	static constexpr bool kUseCustomChecker = false;
	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
