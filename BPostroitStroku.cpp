#include "../algolib/cpplib/base/header.hpp"

class BPostroitStroku {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n, a, b;
			in >> n >> a >> b;
			const int eq = a - b;
			std::string ans(eq, 'a');
			for (int i : range(b)) {
				ans += 'a' + i;
			}
			int curlen = 0;
			while (curlen < n) {
				const int len = std::min(n - curlen, a);
				out << ans.substr(0, len);
				curlen += len;
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
