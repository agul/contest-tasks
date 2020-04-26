#include "base/header.hpp"

class BDvoichniiPeriod {
public:
	void solve(std::istream& in, std::ostream& out) {
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			std::string s;
			in >> s;
			std::vector<int> cnt(2, 0);
			for (char ch : s) {
				cnt[ch - '0']++;
			}

			if (cnt[0] == 0 || cnt[1] == 0) {
				out << s << std::endl;
				continue;
			}
			for (int i : range(cnt[0] + cnt[1])) {
				out << "10";
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
