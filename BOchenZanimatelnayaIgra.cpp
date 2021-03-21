#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/mod_int.hpp"

class BOchenZanimatelnayaIgra {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	std::string make_answer(const int x) {
        const std::string ans = std::to_string(x);
        return std::string(9 - ans.length(), '0') + ans;
	}

	void solve(std::istream& in, std::ostream& out) {
        int a, b, mod;
        in >> a >> b >> mod;

        const ll power = 1'000'000'000;
        for (int x : inclusiveRange(std::min(a, mod - 1))) {
            int value = power * x % mod;
            int cur = 0;
            sub_mod(cur, value, mod);
            if (cur <= b) {
                continue;
            }
            out << 1 << " " << make_answer(x) << std::endl;
            return;
        }
        out << 2 << std::endl;
	}

	BOchenZanimatelnayaIgra() {}

	int naive_solution(const int a, const int b, const int mod) {
	    const ll power = 1'000'000'000;
	    for (int x : inclusiveRange(a)) {
	        bool bad = false;
	        for (int y : inclusiveRange(b)) {
	            const int value = (power * x + y) % mod;
	            if (value == 0) {
	                bad = true;
	                break;
	            }
	        }
	        if (!bad) {
	            return x;
	        }
	    }
	    return -1;
	}

	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    int a, b, mod;
	    in >> a >> b >> mod;
	    const int jans = naive_solution(a, b, mod);

	    int pans;
	    out >> pans;

	    if (jans == -1) {
	        if (pans != 2) {
	            debug("WA should be 2");
	            return false;
	        }
	        return true;
	    }
        const std::string correct = make_answer(jans);
	    if (pans != 1) {
	        debug("WA should be 1 ", correct);
	    }
	    std::string participant;
	    out >> participant;
	    if (correct != participant) {
	        debug("WA can be lower ", correct);
	    }


		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kMaxa = 100;
	    const int kMaxMod = 100;

	    test << Random::get(1, kMaxa) << " " << Random::get(1, kMaxa) << " " << Random::get(1, kMaxMod) << std::endl;
	}

};
