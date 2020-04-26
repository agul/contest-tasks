#include "../algolib/cpplib/base/header.hpp"

class ADreamoonISborMest {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n, x;
			in >> n >> x;
			std::set<int> ranks;
			for (int i : range(1, 220)) {
				ranks.emplace(i);
			}
			for (int i : range(n)) {
				int k;
				in >> k;
				ranks.erase(k);
			}
			for (int i : range(x)) {
				ranks.erase(ranks.begin());
			}
			out << *ranks.begin() - 1 << std::endl;
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
