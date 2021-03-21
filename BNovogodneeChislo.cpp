#include "base/header.hpp"

class BNovogodneeChislo {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        for (int i : range(0, 1000)) {
            if (i * 2020 > n) {
                break;
            }
            int tmp = n - i * 2020;
            if (tmp % 2021 == 0) {
                out << "YES" << std::endl;
                return;
            }
        }
        out << "NO" << std::endl;
	}


	BNovogodneeChislo() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
