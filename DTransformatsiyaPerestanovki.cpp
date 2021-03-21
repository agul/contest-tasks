#include "base/header.hpp"

class DTransformatsiyaPerestanovki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	void go(const std::vector<int>& a, const int l, const int r, const int level, std::vector<int>& ans) {
	    if (l >= r) {
	        return;
	    }
	    int max_index = l;
	    for (int i : range(l, r)) {
	        if (a[i] > a[max_index]) {
	            max_index = i;
	        }
	    }
	    ans[max_index] = level;
	    go(a, l, max_index, level + 1, ans);
	    go(a, max_index + 1, r, level + 1, ans);
	}

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;

        std::vector<int> ans(n, -1);
        go(a, 0, n, 0, ans);

        for (int i : range(n)) {
            out << ans[i] << " ";
        }
        out << std::endl;
	}


	DTransformatsiyaPerestanovki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
