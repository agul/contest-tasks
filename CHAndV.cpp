#include "base/header.hpp"
#include "maths/bits.hpp"

class CHAndV {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m, k;
		in >> n >> m >> k;
		std::vector<std::string> a(n);
		in >> a;

		int ans = 0;
		for (int mask_row : range(1 << n)) {
			auto b = a;
			for (int i : range(n)) {
				if (test_bit(mask_row, i)) {
					for (int j : range(m)) {
						b[i][j] = 'x';
					}
				}
			}
			for (int mask_col : range(1 << m)) {
				auto c = b;
				for (int j : range(m)) {
					if (test_bit(mask_col, j)) {
						for (int i : range(n)) {
							c[i][j] = 'x';
						}
					}
				}
				int cnt = 0;
				for (int i : range(n)) {
					for (int j : range(m)) {
						if (c[i][j] == '#') {
							++cnt;
						}
					}
				}
				if (cnt == k) {
					++ans;
				}
			}
		}
		out << ans << std::endl;
	}


	CHAndV() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
