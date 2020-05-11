#include "base/header.hpp"

class EOsobieElementi {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;
			SafeUnorderedSet<int> elems(all(a));
			for (int i : range(n)) {
				int sum = a[i];
				for (int j : range(i + 1, n)) {
					sum += a[j];
					elems.erase(sum);
				}
			}

			int ans = 0;
			for (int i : a) {
				if (elems.count(i) == 0) {
					++ans;
				}
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
