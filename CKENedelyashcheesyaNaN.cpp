#include "base/header.hpp"

class CKENedelyashcheesyaNaN {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			ll n, k;
			in >> n >> k;
			ll ans = k / (n - 1) * n + k % (n - 1);
			if (ans % n == 0) {
				--ans;
			}
			out << ans << std::endl;
		}
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
