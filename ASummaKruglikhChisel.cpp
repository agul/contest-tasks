#include "base/header.hpp"

class ASummaKruglikhChisel {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			int step = 1;
			std::vector<int> ans;
			while (n > 0) {
				const int digit = n % 10;
				if (digit > 0) {
					ans.emplace_back(digit * step);
				}
				step *= 10;
				n /= 10;
			}
			out << ans.size() << std::endl;
			for (int x : ans) {
				out << x << " " ;
			}
			out << std::endl;
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
