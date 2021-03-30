#include "base/header.hpp"

class ALeshaIPoezd {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<pii> stops(n);
        std::vector<int> delays(n);
        in >> stops >> delays;

        stops.insert(stops.begin(), {0, 0});
        delays.insert(delays.begin(), 0);

        int cur_time = 0;
        for (int i : range(1, n + 1)) {
            const int dist = stops[i].first - stops[i - 1].second;
            cur_time += dist;
            cur_time += delays[i];
            debug("arrival", i, cur_time);

            if (i == n) {
                out << cur_time << std::endl;
                return;
            }

            const int min_stop = (stops[i].second - stops[i].first + 1) / 2;
            debug(i, min_stop);
            const int cur_stop = std::max(0, stops[i].second - cur_time);
            debug(cur_stop);
            debug(min_stop - cur_stop);
            cur_time = std::max(stops[i].second, cur_time) + std::max(min_stop - cur_stop, 0);
            debug("departure", i, cur_time);
        }
	}


	ALeshaIPoezd() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
