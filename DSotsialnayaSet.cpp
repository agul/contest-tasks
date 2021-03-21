#include "base/header.hpp"
#include "collections/queue/queue.hpp"

class DSotsialnayaSet {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, m, t;
        in >> n >> m >> t;
        std::vector<int> times;
        Queue<pii> q(n);

        auto users_cnt = [&q]() {
            if (q.empty()) {
                return 0;
            }

            return q.back().second - q.front().second + 1;
        };

        std::vector<int> ans;
        int index = 0;
        int max_size = 0;
        for (int i : range(n)) {
            std::string s;
            in >> s;

            int hours, minutes, seconds;
            sscanf(s.data(), "%d:%d:%d", &hours, &minutes, &seconds);

            const int cur_time = hours * 3600 + minutes * 60 + seconds;
            while (!q.empty() && q.front().first + t <= cur_time) {
                q.pop_front();
            }
            if (users_cnt() < m) {
                ++index;
            }
            q.push(pii{cur_time, index});
            ans.emplace_back(index);
            umax(max_size, users_cnt());
        }
        if (max_size < m) {
            out << "No solution" << std::endl;
            return;
        }

        out << *max_element(ans) << std::endl;
        for (int x : ans) {
            out << x << std::endl;
        }

	}


	DSotsialnayaSet() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
