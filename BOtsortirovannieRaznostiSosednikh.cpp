#include "../algolib/cpplib/base/header.hpp"

class BOtsortirovannieRaznostiSosednikh {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;
			std::sort(all(a));
			int r = n / 2;
			int l = r - 1;
			while (l >= 0 && r < n) {
				out << a[r++] << " " << a[l--] << " ";
			}
			if (r < n) {
				out << a[r];
			}
			out << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		std::istringstream in(input);
		std::istringstream out(actual_output);

		int tests_count = 0;
		in >> tests_count;
		for (int test : range(tests_count)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;
			out >> a;
			int mx = 0;
			for (int i : range(1, n)) {
				const int diff = abs(a[i] - a[i - 1]);
				if (mx > diff) {
					return false;
				}
				mx = diff;
			}
		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 20;
	static void generate_test(std::ostream& test) {
		const int MAXN = 100000;
		const int MAXM = 1000000;

		test << 1 << std::endl;
		const int N = rand() % MAXN + 1;
		test << N << std::endl;
		for (int i : range(N)) {
			test << rand() % MAXM - (MAXM / 2) << " ";
		}
		test << std::endl;
	}

private:
	size_t test_id_ = 0;
};
