#include "base/header.hpp"

class DFeniksINauka {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			const int steps = 32 - clz(n);
			debug(n, steps);

			std::vector<int> days;
			for (int i : range(steps - 1)) {
				days.emplace_back(1 << i);
			}
			days.emplace_back(n - (days.back() * 2 - 1));
			sort(days);
			debug(days);
			std::vector<int> ans;
			for (int i : range(1, steps)) {
				ans.emplace_back(days[i] - days[i - 1]);
			}
			out << ans.size() << std::endl;
			for (int x : ans) {
				out << x << " ";
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
