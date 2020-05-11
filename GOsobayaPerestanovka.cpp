#include "base/header.hpp"

class GOsobayaPerestanovka {
public:
	static constexpr bool kMultiTest = true;
	static constexpr bool kWriteCaseNumber = true;
	void solve(std::istream& in, std::ostream& out) {
		std::vector<std::vector<int>> rem = {
				{3, 1, 4, 2, 6, 8, 5, 7},
				{1},
				{1, -1, 2},
				{1, 3, -1, 2},
				{3, 1, 4, 2},
				{3, 1, 4, 2, 5},
				{3, 1, 4, 6, 2, 5},
				{3, 1, 4, 6, 2, 5, 7}
		};
		std::vector<bool> pop = {
				false,
				false,
				true,
				true,
				false,
				false,
				false,
				false
		};

		int n;
		in >> n;
		if (n < 4) {
			out << -1 << std::endl;
			return;
		}
		std::vector<int> ans;
		int last = 0;
		for (int i : range(n / 8)) {
			for (int j : rem[0]) {
				ans.emplace_back(j + last);
			}
			last += 8;
		}
		const int remainder = n % 8;
		if (remainder > 0) {
			if (pop[remainder]) {
				ans.pop_back();
			}
			for (int x : rem[remainder]) {
				ans.emplace_back(x + last);
			}
		}
		for (int x : ans) {
			out << x << " ";
		}
		out << std::endl;
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int tests_count;
		in >> tests_count;
		for (int test : range(tests_count)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			out >> a;
			for (int i : range(1, n)) {
				if (abs(a[i] - a[i - 1]) < 2 || abs(a[i] - a[i - 1]) > 4) {
					std::cerr << "FAIL at test case " << test + 1 << ": " << a[i - 1] << " and " << a[i] << std::endl;
					return false;
				}
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {
		out << 1000 << std::endl << 4 << std::endl << 4 << std::endl << 4 << std::endl;
		for (int i : range(4, 1001)) {
			out << i << std::endl;
		}
	}

};
