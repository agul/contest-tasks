#include "base/header.hpp"

class AOtelGilberta {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;
			for (int i : range(n)) {
				a[i] += i;
				a[i] = (a[i] % n + n) % n;
			}
			sort(a);
			unique(a);
			out << (a.size() == n ? "YES" : "NO") << std::endl;
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
