#include "base/header.hpp"
#include "maths/bits.hpp"

class EOcherednoiTurnirSitkhov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		auto p = make_vector<ld>(n, n, 0);
		in >> p;

		std::vector<int> masks((1 << n) - 1);
		std::iota(all(masks), 0);
		sort(masks, [](const int lhs, const int rhs) {
			const int left_pc = popcount(lhs);
			const int right_pc = popcount(rhs);
			return left_pc > right_pc || (left_pc == right_pc && lhs < rhs);
		});

		auto dp = make_vector<ld>(1 << n, n, 0);

		const int full_mask = (1 << n) - 1;
		dp[full_mask][0] = 1;

		for (int mask : masks) {
		    for (int i : range(n)) {
		        if (!test_bit(mask, i)) {
		            continue;
		        }
		        for (int j : range(n)) {
		            if (!test_bit(mask, j)) {
		                const int new_mask = mask ^ (1 << j);
		                umax(dp[mask][i], dp[new_mask][i] * p[i][j] + dp[new_mask][j] * p[j][i]);
		            }
		        }
		    }
		}
        ld ans = 0;
		for (int i : range(n)) {
		    umax(ans, dp[1 << i][i]);
		}
		out << std::fixed << std::setprecision(16) << ans << std::endl;
	}


	EOcherednoiTurnirSitkhov() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		ld jans;
		jury >> jans;

		ld pans;
		out >> pans;

		return std::abs(jans - pans) < EPS;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
