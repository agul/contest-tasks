#include "base/header.hpp"

class BGarriPotterIIstoriyaMagii {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<std::string> a(n);
        in >> a;

        std::vector<int> ans;
        int last = 999;
        for (const auto& x : a) {
            int best = 9999;
            for (int i : range(4)) {
                for (const char ch : inclusiveRange('0', '9')) {
                    std::string tmp = x;
                    tmp[i] = ch;

                    const int value = std::stoi(tmp);
                    if (value < 1000 || value > 2011 || value < last) {
                        continue;
                    }
                    umin(best, value);
                }
            }
            if (best == 9999) {
                out << "No solution" << std::endl;
                return;
            }
            ans.emplace_back(best);
            last = best;
        }
        for (int x : ans) {
            out << x << std::endl;
        }
	}


	BGarriPotterIIstoriyaMagii() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
