#include "base/header.hpp"

class TestTask {
public:
	void solve(std::istream& in, std::ostream& out) {
		char ch = '$';
		debug(ch);

		double a = 2.0;
		debug(a);

		int b = 3;
		debug(b);

		std::vector<int> x{1, 2, 3, 4};
		std::vector<bool> y{true, false, true};

		auto p = std::make_pair(x, y);
		debug(std::make_pair(x, y));

		debug(x);
		debug(y);
		debug(p);

		char s[] = "abc";
		debug(s);

		debug(std::vector<int>{1, 2, 3, 4, 5, 6});

	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
