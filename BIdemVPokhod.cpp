#include "base/header.hpp"

class BIdemVPokhod {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        std::vector<int> less_left(n, 0);
        std::vector<int> less_right(n, 0);

        int mx = 0;
        for (int i : range(1, n)) {
            if (a[i - 1] < a[i]) {
                less_left[i] = less_left[i - 1] + 1;
            } else {
                less_left[i] = 0;
            }
            umax(mx, less_left[i]);
        }
        for (int i : downrange(n - 1)) {
            if (a[i + 1] < a[i]) {
                less_right[i] = less_right[i + 1] + 1;
            } else {
                less_right[i] = 0;
            }

            umax(mx, less_right[i]);
        }

        int cnt = 0;
        for (int i : range(n)) {
            if (less_left[i] == mx || less_right[i] == mx) {
                ++cnt;
            }
        }
        if (cnt > 1) {
            out << 0 << std::endl;
            return;
        }

        int ans = 0;
        for (int i : range(n)) {
            const int min = std::min(less_left[i], less_right[i]);
            if (min == mx && min % 2 == 0) {
                ++ans;
            }
        }
        out << ans << std::endl;
	}


	BIdemVPokhod() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
