#include "base/header.hpp"

class CKhitriiZhuk {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Money = ll;

	// https://codeforces.com/blog/entry/17780
	// https://stackoverflow.com/questions/19524110/find-the-largest-sum-subarray-from-the-given-array-using-segment-trees

	void solve(std::istream& in, std::ostream& out) {
	    int stops_count, passengers_count, fine;
	    in >> stops_count >> passengers_count >> fine;
	    std::vector<int> stops(stops_count);
	    in >> stops;
	    std::vector<int> controller_probability(stops_count - 1);
	    in >> controller_probability;

	    fine *= 2;
	    std::vector<Money> expected_profit(stops_count - 1);
	    for (int i : range(stops_count - 1)) {
	        const ll distance = stops[i + 1] - stops[i];

	        const Money potential_profit = distance * 100;
	        const Money potential_fine = fine * controller_probability[i];
            expected_profit[i] = potential_profit - potential_fine;
	    }

	    Money ans = 0;
	    debug(expected_profit);
	    for (int i : range(passengers_count)) {
	        int from, to;
	        in >> from >> to;
	        --from, --to;

            Money cur_best = 0;
            for (int l : range(from, to)) {
                Money sum = 0;
                for (int r : range(l, to)) {
                    sum += expected_profit[r];
                    umax(cur_best, sum);
                }
            }
            ans += cur_best;
	    }
	    ans /= 2;
	    out << ans / 100 << "." << ans % 100 << "00000" << std::endl;
	}


	CKhitriiZhuk() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
