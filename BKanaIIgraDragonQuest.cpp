#include "../algolib/cpplib/base/header.hpp"

const int kMaxn = 100010;

bool dp[kMaxn + 10][32][32];

class BKanaIIgraDragonQuest {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		fill(dp, 0);
		dp[0][0][0] = true;
		for (int i : range(10)) {
			dp[i][0][1] = true;
		}
		for (int i : range(0, kMaxn)) {
			for (int j : range(0, 31)) {
				for (int k : range(0, 31)) {
					if (dp[i][j][k]) {
						if (i >= 10) {
							const int next = (i - 10) * 2;
							if (next < kMaxn) {
								dp[next][j + 1][k] = true;
								dp[next + 1][j + 1][k] = true;
							}
						}
						const int next = i + 10;
						if (next < kMaxn) {
							dp[next][j][k + 1] = true;
						}
					}
				}
			}
		}
		for (int test_id : range(tests_count)) {
			int x, n, m;
			in >> x >> n >> m;
			bool ok = false;
			for (int i : range(n + 1)) {
				for (int j : range(m + 1)) {
					ok |= dp[x][i][j];
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
