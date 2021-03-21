#include "base/header.hpp"

class CLesenka {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<int> a(n);
        in >> a;

        std::vector<int> right_bound(n);
        right_bound.back() = n - 1;
        for (int i : downrange(n - 1)) {
            if (a[i + 1] < a[i]) {
                right_bound[i] = i;
            } else {
                right_bound[i] = right_bound[i + 1];
            }
        }

        std::vector<int> left_bound(n);
        left_bound.front() = 0;
        for (int i : range(1, n)) {
            if (a[i - 1] < a[i]) {
                left_bound[i] = i;
            } else {
                left_bound[i] = left_bound[i - 1];
            }
        }

        debug(a);
        debug(left_bound);
        debug(right_bound);

        for (int i : range(m)) {
            int l, r;
            in >> l >> r;
            --l, --r;

            bool ans = false;
            if (left_bound[r] <= l || right_bound[l] >= r) {
                ans = true;
            } else {
                const int right_peak = right_bound[l];
                const int left_peak = left_bound[r];
                ans = (left_peak <= right_peak);
                debug(right_peak, left_peak);
            }

            out << (ans ? "Yes" : "No") << std::endl;
        }

	}


	CLesenka() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
