#include "base/header.hpp"

class AMeksimizatsiya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        sort(a);

        SafeUnorderedSet<int> used;
        std::vector<int> b;

        for (int x : a) {
            if (!used.count(x)) {
                used.emplace(x);
                out << x << " ";
            } else {
                b.emplace_back(x);
            }
        }
        for (int x : b) {
            out << x << " ";
        }
        out << std::endl;
	}


	AMeksimizatsiya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
