#include "base/header.hpp"

class AKosmicheskayaNavigatsiya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int x, y;
        std::string s;
        in >> x >> y >> s;

        std::map<char, int> cnt;
        for (const char ch : s) {
            cnt[ch]++;
        }

        bool ok = true;
        if (x > 0) {
            ok &= (cnt['R'] >= x);
        } else {
            ok &= (cnt['L'] >= -x);
        }

        if (y > 0) {
            ok &= (cnt['U'] >= y);
        } else {
            ok &= (cnt['D'] >= -y);
        }

        out << (ok ? "YES" : "NO") << std::endl;
	}


	AKosmicheskayaNavigatsiya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
