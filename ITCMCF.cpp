#include "base/header.hpp"

class ITCMCF {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;

        std::vector<int> negative;
        int cnt = 0;
        int cnt_zeroes = 0;
        for (int i : range(n)) {
            int x;
            in >> x;
            if (x < 0) {
                negative.emplace_back(x);
            }
            else if (x == 0) {
                ++cnt_zeroes;
            } else {
                out << x << " ";
                ++cnt;
            }
        }
        sort(negative, std::greater<>());
        while (negative.size() > 1) {
            out << negative.back() << " ";
            negative.pop_back();
            out << negative.back() << " ";
            negative.pop_back();
            cnt += 2;
        }
        if (cnt == 0) {
            if (cnt_zeroes > 0) {
                out << 0;
            } else {
                out << negative.front();
            }
        }
        out << std::endl;
	}


	ITCMCF() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
