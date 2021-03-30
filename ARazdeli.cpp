#include "base/header.hpp"

class ARazdeli {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        std::string s;
        in >> n >> k >> s;
        for (int len : inclusiveRange(1, n)) {
            if ((n - len) % 2 != 0) {
                continue;
            }
            const int plen = (n - len) / 2;
            if (plen < k) {
                continue;
            }
            std::string a = s.substr(0, plen);
            std::string b = s.substr(plen + len);
            reverse(b);
            if (a == b) {
                out << "YES" << std::endl;
                return;
            }
        }
        out << "NO" << std::endl;
	}


	ARazdeli() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
