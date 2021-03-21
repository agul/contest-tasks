#include "base/header.hpp"

class CSummaKubov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	inline ll cube(const ll x) {
	    return x * x * x;
	}

	void solve(std::istream& in, std::ostream& out) {
        ll x;
        in >> x;

        for (ll i : range(1,11111)) {
            const ll cb = cube(i);
            if (cb > x) {
                break;
            }
            if (cubes.count(x - cb)) {
                out << "YES" << std::endl;
                return;
            }
        }
        out << "NO" << std::endl;
	}

    SafeUnorderedSet<ll> cubes;
	CSummaKubov() {
	    for (ll i : range(1, 11111)) {
	        cubes.emplace(cube(i));
	    }
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
