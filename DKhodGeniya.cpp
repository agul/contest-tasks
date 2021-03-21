#include "base/header.hpp"
#include "maths/bits.hpp"

class DKhodGeniya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int a, b, k;
        in >> a >> b >> k;

        if (b == 1) {
            if (k == 0) {
                std::string s = "1" + std::string(a, '0');
                out << "Yes" << std::endl;
                out << s << std::endl;
                out << s << std::endl;
            } else {
                out << "No" << std::endl;
            }
            return;
        }

        if (a == 0) {
            if (k == 0) {
                out << "Yes" << std::endl;
                out << std::string(b, '1') << std::endl;
                out << std::string(b, '1') << std::endl;
            } else {
                out << "No" << std::endl;
            }
            return;
        }


        std::string s(a + b, '1');
        s.back() = '0';
        --a;

        const int x_pos = s.size() - k - 1;
        if (x_pos <= 0) {
            out << "No" << std::endl;
            return;
        }

        int index = x_pos + 1;
        while (a > 0 && index < s.size() - 1) {
            s[index] = '0';
            ++index;
            --a;
        }

        index = 1;
        while (a > 0 && index < x_pos) {
            s[index] = '0';
            ++index;
            --a;
        }

        debug(s, a);

        if (a > 0) {
            out << "No" << std::endl;
            return;
        }

        out << "Yes" << std::endl;
        out << s << std::endl;

        std::swap(s.back(), s[x_pos]);
        out << s << std::endl;

        /*
        std::map<pii, std::vector<int>> values;
        const int MAXN = 11111;
        for (uint i : range(MAXN)) {
            const int ones = popcount(i);
            const int zeroes = countl_zero(i) - ones;
            values[std::make_pair(ones, zeroes)].emplace_back(i);
        }

        for (const auto& it : values) {
            const auto& vec = it.second;
            const int n = vec.size();
            for (int i : range(n)) {
                for (int j : range(i)) {
                    const int diff = vec[i] - vec[j];
                    if (popcount(diff) > it.first.second) {
                        debug(vec[i], vec[j], diff, it.first, popcount(diff));
                        // return;
                    }
                }
            }
        }
        debug("OK");
        */
	}


	DKhodGeniya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
