#include "base/header.hpp"

class BBerlyandskiiKrossvord {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, U, R, D, L;
        in >> n >> U >> R >> D >> L;
        for (int mask : range(16)) {
            int u = U;
            int r = R;
            int d = D;
            int l = L;
            if (mask & 1) {
                --u;
                --l;
            }
            if (mask & 2) {
                --u;
                --r;
            }
            if (mask & 4) {
                --d;
                --l;
            }
            if (mask & 8) {
                --d;
                --r;
            }
            if (u >= 0 && l >= 0 && r >= 0 && d >= 0 && u <= n - 2 && l <= n - 2 && r <= n - 2 && d <= n - 2) {
                out << "YES" << std::endl;
                return;
            }
        }
        out << "NO" << std::endl;
	}


	BBerlyandskiiKrossvord() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
