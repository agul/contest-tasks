#include "base/header.hpp"

class BMaxIMex {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<int> a(n);
        in >> a;
        debug(a);
        std::set<int> values(all(a));

        int max = *values.rbegin();
        int mex = 0;
        while (values.count(mex) > 0) {
            ++mex;
        }

        for (int i : range(k)) {
            if (max < mex) {
                out << values.size() + k - i << std::endl;
                return;
            }
            const int new_value = (max + mex + 1) / 2;
            values.emplace(new_value);

            const int new_max = *values.rbegin();
            int new_mex = mex;
            while (values.count(new_mex) > 0) {
                ++new_mex;
            }

            if (new_max == max && new_mex == mex) {
                break;
            }
            max = new_max;
            mex = new_mex;
        }
        out << values.size() << std::endl;
	}


	BMaxIMex() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
