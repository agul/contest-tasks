#include "../algolib/cpplib/base/header.hpp"

class BDobriiAnton {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			auto a = std::vector<int>(n);
			auto b = std::vector<int>(n);
			in >> a >> b;
			bool plus = false;
			bool minus = false;
			bool ok = true;
			for (int i : range(n)) {
				if (b[i] < a[i]) {
					ok &= minus;
				}
				if (b[i] > a[i]) {
					ok &= plus;
				}
				plus |= (a[i] == 1);
				minus |= (a[i] == -1);
				// out << ok << " ";
			}
			out << (ok ? "YES" : "NO") << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
