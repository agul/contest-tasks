#include "base/header.hpp"
#include "maths/maths.hpp"

class C2KNOKSlozhnayaVersiya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;

        auto output = [&out](int n, int k) {
        };

        if (k % 2 == n % 2) {
            for (int i : range(k - 2)) {
                --n;
                out << 1 << " ";
            }
            out << n / 2 << " " << n / 2 << std::endl;
            return;
        }
        if (n % 2 == 1) {
            for (int i : range(k - 3)) {
                out << 1 << " ";
                --n;
            }
            k = 3;
        }
        for (int i : range(k - 3)) {
            out << 1 << " ";
            --n;
        }
        if (n % 4 == 0) {
            out << n / 4 << " " << n / 4 << " " << n / 2 << std::endl;
        } else {
            n -= 2;
            out << 2 << " " << n / 2 << " " << n / 2 << std::endl;
        }
	}


	C2KNOKSlozhnayaVersiya() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    int testsCount;
	    in >> testsCount;
	    for (int test_id : range(testsCount)) {
	        int n, k;
	        in >> n >> k;
	        std::vector<int> a(k);
	        out >> a;

	        int cur = 1;
	        int total = 0;
	        for (int x : a) {
	            cur = lcm(cur, x);
	            total += x;
	        }
	        if (total != n || cur > n / 2){
	            debug(n, k, total, cur, n / 2);
	            return false;
	        }
	    }
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
