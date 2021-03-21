#include "base/header.hpp"
#include "maths/prime.hpp"
#include "maths/maths.hpp"

class AExperiment {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
#ifndef HOME
	    assign_files_input_txt();
#endif
        ll n;
        in >> n;

        if (n == 1) {
            out << 1 << std::endl << 1 << std::endl;
            return;
        }

        std::vector<ll> divisors;
        for (int x : primes) {
            ll val = 1;
            while (n % x == 0) {
                n /= x;
                val *= x;
            }
            if (val > 1) {
                divisors.emplace_back(val);
            }
        }
        if (n > 1) {
            divisors.emplace_back(n);
        }

        ll cur = 1;
        ll total = 0;
        for (ll x : divisors) {
            cur = lcm(cur, x);
            total += x;
        }

        if (total > 100000 || cur < n) {
            out << "No solution" << std::endl;
            return;
        }
        out << total << std::endl;
        int index = 1;
        for (ll x : divisors) {
            const int start = index++;
            for (int i : range(x - 1)) {
                out << index++ << " ";
            }
            out << start << " ";
        }
        out << std::endl;
	}

	std::vector<int> primes;

	AExperiment() {
	    primes = primes_vector<int>(100000);
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
