#include "base/header.hpp"

class BIndikatorProgressa {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, k, t;
        in >> n >> k >> t;
        const int total = n * k;
        int shown = 0;
        for (int i : range(n)) {
            if (shown * 100 >= t * total) {
                out << 0 << " ";
                continue;
            }
            if ((shown + k) * 100 <= t * total) {
                out << k << " ";
                shown += k;
                continue;
            }
            bool any = false;
            for (int progress : range(k)) {
                if ((shown + progress + 1) * 100 > t * total) {
                    out << progress << " ";
                    shown += progress;
                    any = true;
                    break;
                }
            }
            if (!any) {
                out << 0 << " ";
            }
        }
        out << std::endl;
	}


	BIndikatorProgressa() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
