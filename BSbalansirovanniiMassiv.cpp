#include "../algolib/cpplib/base/header.hpp"

class BSbalansirovanniiMassiv {
public:
	void solve(std::istream& in, std::ostream& out) {
		int tests_count;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n;
			in >> n;
			if (n % 4 != 0) {
				out << "NO" << std::endl;
				continue;
			}
			out << "YES" << std::endl;
			for (int i : range(n / 4)) {
				const int cur = (i + 1) * 2;
				out << cur << " " << cur + 1000000 << " ";
			}
			for (int i : range(n / 4)) {
				const int cur = (i + 1) * 2;
				out << cur - 1 << " " << cur + 1000000 + 1 << " ";
			}
			out << std::endl;
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
