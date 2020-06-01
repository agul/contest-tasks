#include "base/header.hpp"

class ABerlyandskiiPoker {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, total_jokers, total_players;
		in >> n >> total_jokers >> total_players;

		const int cards_per_player = n / total_players;
		const int max_jokers_for_winner = std::min(cards_per_player, total_jokers);


		const int jokers_left = total_jokers - max_jokers_for_winner;
		const int max_jokers_for_rest = (jokers_left + total_players - 2) / (total_players - 1);
		debug(max_jokers_for_winner, jokers_left, max_jokers_for_rest);
		out << std::max(0, max_jokers_for_winner - max_jokers_for_rest) << std::endl;
	}


	ABerlyandskiiPoker() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
