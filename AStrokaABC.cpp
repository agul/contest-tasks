#include "base/header.hpp"

class AStrokaABC {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        std::string s;
        in >> s;
        for (int mask : range(8)) {
            int balance = 0;
            bool ok = true;
            for (char ch : s) {
                if (mask & (1 << (ch - 'A'))) {
                    ++balance;
                } else {
                    --balance;
                }
                ok &= (balance >= 0);
            }
            ok &= (balance == 0);
            if (ok) {
                out << "YES" << std::endl;
                return;
            }
        }
        out << "NO" << std::endl;
	}


	AStrokaABC() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
