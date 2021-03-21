#include "base/header.hpp"
#include "maths/maths.hpp"

class GStrannayaKrasota {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	const int MAXN = 222222;

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        sort(a);
        std::vector<int> dp(MAXN, 0);

        for (int i : range(n)) {
            const int value = a[i];
            auto divs = divisors_vector(value);
            int cur = 0;
            for (int x : divs) {
                umax(cur, dp[x] + 1);
            }
            umax(dp[value], cur);
        }
        out << n - *max_element(dp) << std::endl;
	}


	GStrannayaKrasota() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
