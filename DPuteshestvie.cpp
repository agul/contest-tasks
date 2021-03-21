#include "base/header.hpp"

class DPuteshestvie {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	const int L = 0;
	const int R = 1;

	void solve(std::istream& in, std::ostream& out) {
        int n;
        std::string s;
        in >> n >> s;

        auto cnt_left = make_vector<int>(n + 1, 2, 0);
        auto cnt_right = make_vector<int>(n + 1, 2, 0);

        for (int i : range(1, n + 1)) {
            if (s[i - 1] == 'L') {
                cnt_left[i][L] = cnt_left[i - 1][R] + 1;
            } else {
                cnt_left[i][R] = cnt_left[i - 1][L] + 1;
            }
        }

        for (int i : downrange(n)) {
            if (s[i] == 'R') {
                cnt_right[i][R] = cnt_right[i + 1][L] + 1;
            } else {
                cnt_right[i][L] = cnt_right[i + 1][R] + 1;
            }
        }

        debug(cnt_left);
        debug(cnt_right);

        std::vector<int> ans(n + 1, 0);
        for (int i : range(n + 1)) {
            ans[i] = 1 + cnt_left[i][L] + cnt_right[i][R];
            out << ans[i] << " ";
        }
        out << std::endl;
	}


	DPuteshestvie() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
