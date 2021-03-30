#include "base/header.hpp"

class CSistemniiAdministrator {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        ll n, m, v;
        in >> n >> m >> v;
        --v;
        const int other = (v == 0 ? 1 : 0);
        if (m < n - 1 || m > (n - 2) * (n - 3) / 2 + (n - 1)) {
            out << -1 << std::endl;
            return;
        }
        for (int i : range(n)) {
            if (i != v) {
                out << v + 1 << " " << i + 1 << std::endl;
                --m;
            }
        }
        for (int i : range(n)) {
            if (m == 0) {
                break;
            }
            if (i == other || i == v) {
                continue;
            }
            for (int j : range<ll>(i + 1, n)) {
                if (m == 0) {
                    break;
                }
                if (j == other || j == v) {
                    continue;
                }
                --m;
                out << i + 1 << " " << j + 1 << std::endl;
            }
        }
	}


	CSistemniiAdministrator() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
