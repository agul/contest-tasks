#include "base/header.hpp"

class BCubes {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        std::string s, t;
        int n;
        in >> s >> n;
        for (int i : range(n)) {
            std::string q;
            in >> q;
            t += q;
        }
        sort(s);
        sort(t);
        out << (s == t ? "YES" : "NO") << std::endl;
	}


	BCubes() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
