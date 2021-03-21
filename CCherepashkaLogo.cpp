#include "base/header.hpp"

class CCherepashkaLogo {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

    const int N = 0;
    const int S = 1;

    const int F = 0;
    const int T = 1;

    const int DX[2] = {1, -1};

    const int kMaxPos = 222;
    const int kStartingPos = 110;

	void solve(std::istream& in, std::ostream& out) {
        std::string commands;
        int max_changes;
        in >> commands >> max_changes;

        const int n = commands.size();
        commands += "#";
        auto dp = make_vector<bool>(n + 1, max_changes + 2, kMaxPos, 2, 3, 0);

        auto get_command = [this](const char command) {
            if (command == '#') {
                return 2;
            }
            return (command == 'F' ? F : T);
        };

        dp[0][0][kStartingPos][N][get_command(commands.front())] = true;

        for (int command_id : range(n)) {
            for (int changes : inclusiveRange(max_changes)) {
                for (int pos : range(kMaxPos)) {
                    for (int dir : range(2)) {
                        for (int command : range(2)) {
                            if (!dp[command_id][changes][pos][dir][command]) {
                                continue;
                            }
                            const int next_command = get_command(commands[command_id + 1]);
                            if (command == T) {
                                dp[command_id + 1][changes][pos][1 - dir][next_command] = true;
                                dp[command_id][changes + 1][pos][dir][F] = true;
                            } else {
                                dp[command_id + 1][changes][pos + DX[dir]][dir][next_command] = true;
                                dp[command_id][changes + 1][pos][dir][T] = true;
                            }
                        }
                    }
                }
            }
        }

        int ans = 0;
        for (int pos : range(kMaxPos)) {
            for (int dir : range(2)) {
                if (dp[n][max_changes][pos][dir][2]) {
                    umax(ans, std::abs(pos - kStartingPos));
                }
            }
        }
        out << ans << std::endl;

	}


	CCherepashkaLogo() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
