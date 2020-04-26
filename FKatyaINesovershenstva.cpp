#include "../algolib/cpplib/base/header.hpp"
#include "../algolib/cpplib/maths/maths.hpp"

class FKatyaINesovershenstva {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int n;
		in >> n;
		std::vector<int> div(n + 1, 1);
		for (int j : range(2, n)) {
			for (int k = j * 2; k <= n; k += j) {
				umax(div[k], j);
			}
		}
		std::vector<int> ans;
		for (int i : range(2, n + 1)) {
			ans.emplace_back(div[i]);
		}
		std::sort(all(ans));
		for (int x : ans) {
			out << x << " ";
		}
		out << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
