#include "../algolib/cpplib/base/header.hpp"

class TCO20_1A_easy {
public:
	double nonDuplicatedAverage(std::vector <int> prices) {
		double ans = 0;
		std::set<int> used;
		for (int x : prices) {
			if (used.count(x)) {
				continue;
			}
			used.emplace(x);
			ans += x;
		}
		ans /= used.size();
		return ans;
	}

	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;
		out << nonDuplicatedAverage(a) << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
