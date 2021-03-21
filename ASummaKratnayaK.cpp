#include "base/header.hpp"

class ASummaKratnayaK {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        if (k < n) {
            if (n % k == 0) {
                k = n;
            } else {
                k = n + k - n % k;
            }
        }
        const int div = k / n;
        if (k % n > 0) {
            out << div + 1 << std::endl;
        } else {
            out << div << std::endl;
        }
	}


	ASummaKratnayaK() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
