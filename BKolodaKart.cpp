#include "base/header.hpp"

class BKolodaKart {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        std::set<int> values;
        for (int i : range(1, n + 1)) {
            values.emplace(i);
        }

        std::vector<int> ans;
        while (!values.empty()) {
            const int cur_max = *values.rbegin();
            int index = a.size() - 1;
            int end = a.size();
            while (index >= 0 && a[index] != cur_max) {
                --index;
            }

            for (int i : range(index, end)) {
                ans.emplace_back(a[i]);
            }

            for (int i : range(index, end)) {
                values.erase(a.back());
                a.pop_back();
            }
        }
        for (int i : ans) {
            out << i << " ";
        }
        out << std::endl;
	}


	BKolodaKart() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
