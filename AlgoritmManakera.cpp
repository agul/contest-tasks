#include "base/header.hpp"
#include "string/manacher.hpp"

class AlgoritmManakera {
public:
	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		in >> s;
		const auto palindromes = count_palindromes(s);
		out << std::accumulate(all(palindromes), 0LL) << std::endl;
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
