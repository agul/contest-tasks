#include "base/header.hpp"

class BChastichnayaZamena {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        std::string s;
        in >> n >> k >> s;

        int left = s.find('*');
        int right = s.rfind('*');
        int ans = (left == right ? 1 : 2);

        while (right - left > k) {
            {
                int pos = left;
                int prev = -1;
                while (pos - left <= k) {
                    prev = pos;
                    pos = s.find('*', pos + 1);
                }

                ++ans;
                left = prev;
                debug(left);
            }

            if (right - left > k) {
                int pos = right;
                int prev = -1;
                while (right - pos <= k) {
                    prev = pos;
                    pos = s.rfind('*', pos - 1);
                }

                ++ans;
                right = prev;
                debug(right);
            }
        }
        out << ans << std::endl;
	}


	BChastichnayaZamena() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
