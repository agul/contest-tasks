#include "base/header.hpp"

class AFeniksIBalans {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			ll sumA = 0;
			ll sumB = 0;
			for (int i : range(1, n / 2)) {
				sumA += (1 << i);
			}
			for (int i : range(n / 2, n)) {
				sumB += (1 << i);
			}
			sumA += (1 << n);
			out << sumA - sumB << std::endl;

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
