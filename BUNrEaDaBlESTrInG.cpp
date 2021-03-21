#include "base/header.hpp"

class BUNrEaDaBlESTrInG {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        std::string s;
        in >> s;
        bool ok = true;
        for (int i : range(s.length())) {
            if (i & 1) {
                ok &= (s[i] >= 'A' && s[i] <= 'Z');
            } else {
                ok &= (s[i] >= 'a' && s[i] <= 'z');
            }
        }
        out << (ok ? "Yes" : "No") << std::endl;
	}


	BUNrEaDaBlESTrInG() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
