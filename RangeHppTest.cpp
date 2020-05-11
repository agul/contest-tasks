#include "base/header.hpp"

class RangeHppTest {
public:

	template<typename T>
	bool check(const T& range, const std::vector<int>& expected) {
		const std::vector<int> a(all(range));
		assert(a == expected);
		return true;
	}

	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		check(range(5), {0, 1, 2, 3, 4});
		check(inclusiveRange(5), {0, 1, 2, 3, 4, 5});

		check(downrange(5), {4, 3, 2, 1, 0});
		check(inclusiveDownrange(5), {5, 4, 3, 2, 1, 0});

		check(range(2, 5), {2, 3, 4});
		check(inclusiveRange(2, 5), {2, 3, 4, 5});

		check(downrange(5, 2), {4, 3, 2});
		check(inclusiveDownrange(5, 2), {5, 4, 3, 2});

		check(reversed(std::vector<int>{1, 2, 3, 4, 5}), {5, 4, 3, 2, 1});
		std::vector<int> tmp;
		tmp = {5, 4, 3, 2, 1};
		check(reversed(tmp), {1, 2, 3, 4, 5});

		out << "OK" << std::endl;
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {}

};
