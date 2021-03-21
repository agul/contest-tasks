#include "base/header.hpp"

class C1DSokoban {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	int solve(const std::vector<int>& boxes, const std::vector<int>& positions) {
	    const int n = boxes.size();
	    const int m = positions.size();

	    std::vector<int> already_ok(m + 1, 0);

        {
            int index = n - 1;
            for (int i : downrange(m)) {
                already_ok[i] = already_ok[i + 1];
                while (index >= 0 && boxes[index] > positions[i]) {
                    --index;
                }
                if (index < 0) {
                    break;
                }
                if (boxes[index] < positions[i]) {
                    continue;
                }
                already_ok[i] += 1;
            }
        }

	    int ans = 0;
	    int box_index = 0;
	    int prev = 0;
	    for (int i : range(m)) {
	        umax(ans, already_ok[i]);

	        const int cur_pos = positions[i];
            while (box_index < n && boxes[box_index] <= cur_pos) {
                ++box_index;
            }
            while (prev < m && positions[prev] + box_index - 1 < cur_pos) {
                ++prev;
            }
            if (prev > i) {
                continue;
            }

            umax(ans, already_ok[i + 1] + i - prev + 1);
	    }

	    return ans;
	}

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<int> boxes(n), positions(m);
        in >> boxes >> positions;

        int ans = 0;
        {
            std::vector<int> b, p;
            for (int i : downrange(n)) {
                if (boxes[i] < 0) {
                    b.emplace_back(-boxes[i]);
                }
            }
            for (int i : downrange(m)) {
                if (positions[i] < 0) {
                    p.emplace_back(-positions[i]);
                }
            }
            ans += solve(b, p);
        }
        {
            std::vector<int> b, p;
            for (int i : range(n)) {
                if (boxes[i] > 0) {
                    b.emplace_back(boxes[i]);
                }
            }
            for (int i : range(m)) {
                if (positions[i] > 0) {
                    p.emplace_back(positions[i]);
                }
            }
            ans += solve(b, p);
        }
        out << ans << std::endl;
	}


	C1DSokoban() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
