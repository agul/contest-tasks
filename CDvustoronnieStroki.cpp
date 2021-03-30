#include "base/header.hpp"
#include "hash/double_hasher.hpp"
#include "hash/hasher.hpp"

class CDvustoronnieStroki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        std::string a, b;
        in >> a >> b;

        Hasher<DoubleHasher<ll>> ha(a), hb(b);
        const int sum = a.length() + b.length();
        int ans = sum;
        for (int len : inclusiveRange(std::min(a.length(), b.length()))) {
            for (int x : range(a.length() - len + 1)) {
                for (int y : range(b.length() - len + 1)) {
                    if (ha.get_hash(x, x + len - 1) == hb.get_hash(y, y + len - 1)) {
                        umin(ans, sum - len * 2);
                    }
                }
            }
        }
        out << ans << std::endl;
	}


	CDvustoronnieStroki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
