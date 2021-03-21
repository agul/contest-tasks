#include "base/header.hpp"

class KRating {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<pii> teams(n);
        in >> teams;

        for (auto& x : teams) {
            if (x.first < x.second) {
                std::swap(x.first, x.second);
            }
        }

        if (n == 1) {
            out << "YES" << std::endl;
            return;
        }

        double upper = 1;
        double lower = 0;
        for (int i : range(n - 1)) {
            const double a = teams[i].first;
            const double b = teams[i].second;
            const double c = teams[i + 1].first;
            const double d = teams[i + 1].second;

            const double x = d - b;
            const double y = a - b - c + d;
            if (is_equal_to_zero(y)) {
                if (x > EPS) {
                    out << "NO" << std::endl;
                    return;
                }
            }
            if (y < -EPS) {
                umin(upper, x / y);
            } else {
                umax(lower, x / y);
            }
        }
        if (upper + EPS < lower) {
            out << "NO" << std::endl;
        } else {
            out << "YES" << std::endl;
        }
	}


	KRating() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
