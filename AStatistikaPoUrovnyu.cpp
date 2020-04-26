#include "../algolib/cpplib/base/header.hpp"

class AStatistikaPoUrovnyu {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			auto b = make_vector<int>(n, 0);
			for (int i : range(n)) {
				in >> a[i] >> b[i];
			}
			bool ok = true;
			for (int i : range(n)) {
				ok &= (a[i] >= b[i]);
				if (i > 0) {
					ok &= (a[i] - a[i - 1] >= b[i] - b[i - 1] && a[i] >= a[i - 1] && b[i] >= b[i - 1]);
				}
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
