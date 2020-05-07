#include "base/header.hpp"
#include "string/z_function.hpp"

class ZFunktsiya {
public:
	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		in >> s;
		const auto z = z_function(s);
		for (const auto& it : z) {
			out << it << " ";
		}
		out << std::endl;
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
