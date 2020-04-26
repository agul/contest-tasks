#include "../algolib/cpplib/base/header.hpp"

class AKonfetiIDveSestri {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			if (n < 3) {
				out << 0 << std::endl;
				continue;
			}
			int x = n / 2;
			int ans = n - 1 - x;
			out << ans << std::endl;
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
