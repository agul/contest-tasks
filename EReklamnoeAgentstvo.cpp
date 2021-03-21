#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/mod_int.hpp"

class EReklamnoeAgentstvo {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	static const int MOD = 1000000007;
	using Int = ModInt<ll, MOD>;

	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<int> bloggers(n);
        in >> bloggers;
        sort(bloggers, std::greater<>());
        int last = -1;
        int index = 0;
        Int ans = 1;
        while (index < n && k > 0) {
            int cnt = 0;
            const int cur = bloggers[index];
            while (index < n && bloggers[index] == cur) {
                ++cnt;
                ++index;
            }
            if (cnt >= k) {
                ans *= factorial<Int>(cnt) * factorial<Int>(k).inverse() * factorial<Int>(cnt - k).inverse();
            }
            k -= cnt;
        }
        out << ans << std::endl;
	}


	EReklamnoeAgentstvo() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
