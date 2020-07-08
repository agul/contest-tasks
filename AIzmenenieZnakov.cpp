#include "base/header.hpp"

class AIzmenenieZnakov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		for (int i : range(n)) {
			if (i % 2 == 1) {
				a[i] = -std::abs(a[i]);
			} else {
				a[i] = std::abs(a[i]);
			}
		}

		for (int x : a) {
			out << x << " ";
		}
		out << std::endl;
	}


	AIzmenenieZnakov() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;
		for (int testid : range(testsCount)) {
			int n;
			in >> n;
			std::vector<int> a(n);
			in >> a;
			out >> a;

			int cnt_less = 0;
			int cnt_more = 0;

			for (int i : range(1, n)) {
				if (a[i] - a[i - 1] >= 0) {
					cnt_more += 1;
				}
				if (a[i] - a[i - 1] <= 0) {
					cnt_less += 1;
				}
			}
			if (cnt_more < n / 2 || cnt_less < n / 2) {
				debug(testid, n, cnt_more, cnt_less);
				return false;
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
