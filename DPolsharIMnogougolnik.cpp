#include "base/header.hpp"
#include "cpplib/data_structures/fenwick_tree/fenwick_tree.hpp"

class DPolsharIMnogougolnik {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        if (k > n / 2) {
            k = n - k;
        }
        FenwickTreeSum<int> segments(n);
        ll ans = 1;
        int cur = 0;
        for (int i : range(n)) {
            const int next = (cur + k) % n;
            int lines = 0;

            if (next < cur) {
                lines += segments.query(cur + 1, n - 1);
                lines += segments.query(0, next - 1);
            } else {
                lines += segments.query(cur + 1, next - 1);
            }

            debug(cur, next, lines);

            segments.inc(cur, 1);
            segments.inc(next, 1);
            cur = next;

            ans += lines + 1;
            out << ans << " ";
        }
        out << std::endl;

	}


	DPolsharIMnogougolnik() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
