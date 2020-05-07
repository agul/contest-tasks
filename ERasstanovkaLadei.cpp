#include "base/header.hpp"

class ERasstanovkaLadei {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		int M = n * n;
		auto field = make_vector<int>(n, n, 0);
		int ans = 0;
		for (int mask = 0; mask < (1 << M); ++mask) {
			if (popcount(mask) != n) {
				continue;
			}
			// debug(mask);
			field = make_vector<int>(n, n, 0);
			std::vector<bool> used_cols(n, false);
			std::vector<bool> used_rows(n, false);
			for (int i : range(M)) {
				if (mask & (1 << i)) {
					field[i / n][i % n] = 1;
					used_rows[i / n] = true;
					used_cols[i % n] = true;
				}
			}
			bool ok = true;
			for (int i : range(n)) {
				for (int j : range(n)) {
					ok &= (used_cols[i] || used_rows[j]);
				}
			}
			if (!ok) {
				continue;
			}
			int pairs = 0;
			for (int i : range(n)) {
				bool any = false;
				for (int j : range(n)) {
					if (field[i][j] == 1) {
						if (any) {
							pairs += 1;
						} else {
							any = true;
						}
					}
				}
			}
			for (int i : range(n)) {
				bool any = false;
				for (int j : range(n)) {
					if (field[j][i] == 1) {
						if (any) {
							pairs += 1;
						} else {
							any = true;
						}
					}
				}
			}
			if (pairs == k) {
				++ans;
			}
		}
		out << ans << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
