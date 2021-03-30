#include "base/header.hpp"
#include "maths/bits.hpp"

class BKorobka {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, w;
        in >> n >> w;
        std::vector<int> a(n);
        in >> a;

        std::vector<int> cnt(20, 0);
        for (int x : a) {
            cnt[binary_power(x)]++;
        }

        int levels = 0;
        int rem = n;
        while (rem > 0) {
            ++levels;
            int width = w;
            int index = 19;
            while (rem > 0 && index >= 0) {
                if (cnt[index] > 0 && width >= (1 << index)) {
                    width -= (1 << index);
                    --rem;
                    --cnt[index];
                } else {
                    --index;
                }
            }
        }
        out << levels << std::endl;
	}


	BKorobka() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
