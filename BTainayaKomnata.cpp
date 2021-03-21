#include "base/header.hpp"

class BTainayaKomnata {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct State {
	    int x, y;
	    Direction dir;
	};

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;
        std::vector<std::string> field(n);
        in >> field;

        auto out_of_bounds = [&n, &m](const int x, const int y) {
            return x < 0 || y < 0 || x >= n || y >= m;
        };

        auto is_column = [&field](const int x, const int y) {
            return field[x][y] == '#';
        };

        auto dp = make_vector<int>(n, m, 4, INF);
        std::deque<State> q(n * m * 4);
        auto add = [&q, &dp, &out_of_bounds](const int x, const int y, const Direction dir, const int cur_len, const int delta) {
            if (out_of_bounds(x, y)) {
                return;
            }
            const int value = dp[x][y][dir];
            if (umin(dp[x][y][dir], cur_len + delta)) {
                if (value == INF) {
                    if (delta == 0) {
                        q.push_front(State{x, y, dir});
                    } else {
                        q.push_back(State{x, y, dir});
                    }
                }
            }
        };

        add(n - 1, m - 1, Direction::West, 0, 0);
        while (!q.empty()) {
            const State state = q.front();
            q.pop_front();

            const int x = state.x;
            const int y = state.y;
            // debug(x, y);
            const Direction dir = state.dir;
            const int cur_len = dp[x][y][dir];
            add(x + DX[state.dir], y + DY[state.dir], dir, cur_len, 0);

            if (is_column(x, y)) {
                for (int new_dir : range(4)) {
                    add(x, y, Direction(new_dir), cur_len, 1);
                }
            }
        }
        
        const int ans = dp[0][0][Direction::West];
        out << (ans == INF ? -1 : ans) << std::endl;
	}


	BTainayaKomnata() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
