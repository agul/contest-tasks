#include "base/header.hpp"

class CNastyaIStranniiGenerator {
public:
	void solve(std::istream& in, std::ostream& out) {
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;
			auto b = make_vector<int>(n, -1);
			for (int i : range(n)) {
				--a[i];
				b[a[i]] = i;
			}

			auto used = make_vector<int>(n, -1);
			bool ok = true;
			bool any = true;
			int last = -1;
			for (int i : range(n)) {
				if (last >= n || used[last] != -1) {
					any = true;
				}
				if (any) {
					any = false;
					used[b[i]] = i;
					last = b[i] + 1;
					continue;
				}
				if (b[i] != last) {
					debug(i, b[i], last);
					ok = false;
					break;
				}
				used[b[i]] = i;
				++last;
			}

			out << (ok ? "Yes" : "No") << std::endl;
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
