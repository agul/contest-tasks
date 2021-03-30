#include "base/header.hpp"
#include "string/utils.hpp"

class AAvtodopolnenie {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        std::string type;
        int n;
        in >> type >> n;
        std::vector<std::string> a(n);
        in >> a;

        std::string ans(1, 127);
        for (const auto& x : a) {
            if (starts_with(x, type)) {
                umin(ans, x);
            }
        }
        out << (ans.back() == 127 ? type : ans) << std::endl;
	}


	AAvtodopolnenie() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
