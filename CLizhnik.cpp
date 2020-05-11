#include "base/header.hpp"

class CLizhnik {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		in >> s;
		int x = 0;
		int y = 0;
		int ans = 0;
		using Node = std::pair<pii, Direction>;
		std::set<Node> ways;

		auto move = [&ans, &ways](int& x, int& y, const Direction dir) {
			const int nx = x + DX[dir];
			const int ny = y + DY[dir];
			if (ways.count({{x, y}, dir}) > 0) {
				ans += 1;
				x = nx;
				y = ny;
				return;
			}
			ans += 5;
			ways.insert(std::make_pair(pii{x, y}, dir));
			ways.insert(Node(pii{nx, ny}, Direction(dir ^ 2)));
			x = nx;
			y = ny;
		};

		for (char ch : s) {
			Direction dir = Direction::Unknown;
			if (ch == 'N') {
				dir = Direction::North;
			}
			else if (ch == 'S') {
				dir = Direction::South;
			}
			else if (ch == 'W') {
				dir = Direction::West;
			}
			else if (ch == 'E') {
				dir = Direction::East;
			}
			move(x, y, dir);
		}
		out << ans << std::endl;
	}


	CLizhnik() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& out) {}

};
