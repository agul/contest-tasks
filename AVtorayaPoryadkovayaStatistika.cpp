#include "base/header.hpp"

class AVtorayaPoryadkovayaStatistika {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> b(n);
        in >> b;

        std::set<int> a(all(b));
        a.erase(a.begin());
        if (a.empty()) {
            out << "NO" << std::endl;
        } else {
            out << *a.begin() << std::endl;
        }
	}


	AVtorayaPoryadkovayaStatistika() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
