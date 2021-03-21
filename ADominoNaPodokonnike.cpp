#include "base/header.hpp"

class ADominoNaPodokonnike {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, k1, k2, w, b;
        in >> n >> k1 >> k2 >> w >> b;
        if (k1 < k2) {
            std::swap(k1, k2);
        }
        int b1 = n - k1;
        int b2 = n - k2;
        k1 -= k2;
        b2 -= b1;
        const int cnt_white = k2 + k1 / 2;
        const int cnt_black = b1 + b2 / 2;
        if (cnt_white < w || cnt_black < b) {
            out << "NO" << std::endl;
            return;
        }
        out << "YES" << std::endl;
	}


	ADominoNaPodokonnike() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
