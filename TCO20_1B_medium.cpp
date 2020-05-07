#include "base/header.hpp"

class EllysWhatDidYouGet {
public:
	int getCount(int N) {
		sums = std::vector<int>(300000, 0);
		for (int i = 0; i < sums.size(); ++i) {
			int cur = i;
			int sum = 0;
			while (cur > 0) {
				sum += cur % 10;
				cur /= 10;
			}
			sums[i] = sum;
		}

		int ans = 0;
		for (int x = 1; x <= 50; ++x) {
			for (int y = 1; y <= 50; ++y) {
				for (int z = 1; z <= 50; ++z) {
					int cur_ans = -1;
					bool ok = true;
					bool first = true;
					for (int i = 1; i <= N; ++i) {
						int cur = (i * x + y) * z;
						if (first) {
							cur_ans = sums[cur];
							first = false;
						}
						ok &= (cur_ans == sums[cur]);
					}
					if (ok) {
						++ans;
					}
				}
			}
		}
		return ans;
	}

	std::vector<int> sums;
};

class TCO20_1B_medium {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int n;
		in >> n;

		EllysWhatDidYouGet solution;
		out << solution.getCount(n) << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
