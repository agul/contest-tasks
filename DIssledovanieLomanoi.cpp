#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/rational.hpp"

class DIssledovanieLomanoi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<Rational<int>> a;
        for (int i : range(n)) {
            int k, b;
            in >> k >> b;
            if (k == 0) {
                continue;
            }
            a.emplace_back(Rational<int>(k, b));
        }
        sort(a);
        unique(a);

        out << a.size() << std::endl;
	}


	DIssledovanieLomanoi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
