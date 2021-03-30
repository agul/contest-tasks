#include "base/header.hpp"

class DEpicheskayaTransformatsiya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        SafeUnorderedMap<int, int> cnt;
        for (int x : range(n)) {
            int cur;
            in >> cur;
            ++cnt[cur];
        }

        int ans = n % 2;
        for (const auto& it : cnt) {
            umax(ans, std::max(0, it.second * 2 - n));
        }
        out << ans << std::endl;
	}


	DEpicheskayaTransformatsiya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
