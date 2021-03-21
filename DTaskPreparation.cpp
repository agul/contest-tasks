#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/prime.hpp"
#include "data_structures/fenwick_tree.hpp"

class DTaskPreparation {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	static constexpr int kMaxn = 555555;

	void solve(std::istream& in, std::ostream& out) {
        int n, queries_count;
        in >> n >> queries_count;
        std::vector<int> a(n);
        in >> a;

        FenwickTreeSumRangeUpdates<ll> fenwick(kMaxn);
        for (int x : a) {
            for
        }
	}

    std::vector<std::vector<int>> divisors;

	DTaskPreparation() : divisors(kMaxn) {
        for (int i : range(1, kMaxn)) {
            divisors[i] = divisors_vector(i);
            sort(divisors[i]);
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
