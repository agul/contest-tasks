#include "base/header.hpp"
#include "maths/maths.hpp"

class AZadachaODelimosti {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			ll a, b;
			in >> a >> b;
			debug(test, a, b);
			out << ((a - 1) / b + 1) * b - a << std::endl;
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
