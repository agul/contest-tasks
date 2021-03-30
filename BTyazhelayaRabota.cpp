#include "base/header.hpp"
#include "string/utils.hpp"

class BTyazhelayaRabota {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        std::string a, b, c;
        in >> a >> b >> c;

        auto normalize = [](std::string& s) {
            std::string ans = "";
            for (const char ch : s) {
                if (isalpha(ch)) {
                    ans += to_lower(ch);
                }
            }
            ans.swap(s);
        };

        normalize(a);
        normalize(b);
        normalize(c);
        std::unordered_set<std::string> valid = {
                a + b + c,
                a + c + b,
                b + a + c,
                b + c + a,
                c + a + b,
                c + b + a
        };
        int n;
        in >> n;
        for (int i : range(n)) {
            std::string s;
            in >> s;
            normalize(s);
            out << (valid.count(s) ? "ACC" : "WA") << std::endl;
        }
	}


	BTyazhelayaRabota() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
