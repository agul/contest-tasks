#include "base/header.hpp"

class CheatingDetection {
public:
	static constexpr bool kWriteCaseNumber = true;
	static constexpr bool kMultiTest = true;

	static constexpr int kPlayersCount = 100;
	static constexpr int kQuestionsCount = 10000;
	static constexpr int kMostDifficult = 20;

	bool first = true;

	void solve(std::istream& in, std::ostream& out) {
	    if (first) {
	        int p;
	        in >> p;
	        first = false;
	    }
        std::vector<std::string> players(kPlayersCount);
	    in >> players;
	    std::vector<pii> questions;
	    for (int q : range(kQuestionsCount)) {
	        int cur = 0;
	        for (const auto& player : players) {
                cur += player[q] - '0';
	        }
	        questions.emplace_back(cur, q);
	    }
	    sort(questions);

        int max_solved = -1;
        int min_diff = INF;
        int ans = -1;
	    for (int i : range(kPlayersCount)) {
	        int cnt_solved = 0;
            for (int j : range(kMostDifficult)) {
                cnt_solved += players[i][questions[j].second] - '0';
            }
            // if (umax(max_solved, cnt_solved)) {
            if (umin(min_diff, std::abs(cnt_solved - kMostDifficult / 2))) {
                ans = i;
            }
        }
	    out << ans + 1 << std::endl;
	    debug(ans);
	}


	CheatingDetection() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    int testsCount, p;
	    in >> testsCount >> p;
	    const int kMinSuccessTests = (p * testsCount + 99) / 100;
	    std::vector<int> pans;
	    for (int _ : range(testsCount)) {
	        std::string skip;
	        for (int i : range(kPlayersCount)) {
	            in >> skip;
	        }
	        int cur_pans;
	        out >> skip >> skip >> cur_pans;
	        pans.emplace_back(cur_pans);
	    }
	    std::vector<int> jans(testsCount);
	    in >> jans;
	    int success = 0;
        debug(pans);
        debug(jans);
	    for (int i : range(testsCount)) {
	        if (jans[i] == pans[i]) {
	            ++success;
	            debug(i, jans[i]);
	        }
	    }
	    debug(success, kMinSuccessTests);
		return success >= kMinSuccessTests;
	}


	static constexpr size_t kGeneratedTestsCount = 1;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kTestsCount = 50;
        const int kMinValue = -3;
        const int kMaxValue = 3;
        const int kMultiplier = 100000;

	    auto generate_value = []() {
            const double median = (kMinValue + kMaxValue) / 2.0;
	        return static_cast<double>(Random::get(0, (kMaxValue - kMinValue) * kMultiplier)) / kMultiplier - median;
	    };

	    auto sigmoid = [](const double x) {
	        return 1.0 / (1 + std::exp(-x));
	    };

	    auto solved = [&sigmoid](const double players_skill, const double question_difficulty) {
	        const double probability = sigmoid(players_skill - question_difficulty);
            return Random::get(0, kMultiplier) <= static_cast<int>(probability * kMultiplier);
	    };

        auto will_cheat = []() {
            return Random::get(0, 1) == 0;
        };

        debug("HELLO");
	    test << kTestsCount << std::endl;
	    test << 10 << std::endl;
	    std::vector<int> cheaters;
	    for (int _ : range(kTestsCount)) {
            debug(_);
            std::vector<double> questions(kQuestionsCount);
            for (auto &question : questions) {
                question = generate_value();
            }

            std::vector<double> players(kPlayersCount);
            for (auto &player : players) {
                player = generate_value();
            }

            const int cheater_id = Random::get(0, kPlayersCount - 1);
            cheaters.emplace_back(cheater_id);

            for (int player_id : range(kPlayersCount)) {
                const double player = players[player_id];
                const bool is_cheater = (player == cheater_id);

                std::string answers;
                answers.reserve(kQuestionsCount);
                for (const double question : questions) {
                    if (is_cheater && will_cheat() || solved(player, question)) {
                        answers += '1';
                    } else {
                        answers += '0';
                    }
                }
                test << answers << std::endl;
            }
        }
	    for (int x : cheaters) {
	        test << x + 1 << std::endl;
	    }
	    debug(cheaters);
	}

	static constexpr bool kSkipPrintingTestInput = true;
};
