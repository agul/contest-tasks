#include "../algolib/cpplib/base/header.hpp"

class DAntiSudoku {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			std::vector<std::string> field(9);
			in >> field;
			for (int i : range(3)) {
				for (int j : range(3)) {
					int x = i * 3 + j;
					int y = j * 3 + i;
					if (field[x][y] == '1') {
						field[x][y] = '6';
					} else {
						field[x][y] = '1';
					}
				}
			}
			for (const auto& row : field) {
				out << row << std::endl;
			}
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		for (int )
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
