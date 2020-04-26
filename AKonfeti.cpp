#include "../algolib/cpplib/base/header.hpp"

class AKonfeti {
public:
	void solve(std::istream& in, std::ostream& out) {
		int tests_count;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			ll n;
			in >> n;
			ll cur = 4;
			while (cur <= n + 1) {
				if (n % (cur - 1) == 0) {
					out << n / (cur - 1) << std::endl;
					break;
				}
				cur <<= 1;
			}
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
