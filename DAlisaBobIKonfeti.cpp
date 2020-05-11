#include "base/header.hpp"

class DAlisaBobIKonfeti {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;
			int steps = 0;
			int alice = 0;
			int bob = 0;
			int last = 0;
			int left = 0;
			int right = n - 1;
			while (left <= right) {
				int sum = 0;
				if (steps & 1) {
					while (left <= right && sum <= last) {
						sum += a[right];
						--right;
					}
					bob += sum;
				} else {
					while (left <= right && sum <= last) {
						sum += a[left];
						++left;
					}
					alice += sum;
				}
				last = sum;
				++steps;
			}
			out << steps << " " << alice << " " << bob << std::endl;
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
