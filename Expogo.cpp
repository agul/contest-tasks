#include "../algolib/cpplib/base/header.hpp"

const std::string WAYS = "XWNES";
const std::unordered_map<char, Direction> dirs{
		{'W', Direction::North},
		{'N', Direction::East},
		{'E', Direction::South},
		{'S', Direction::West},
		{'X', Direction::Unknown}
};

class Expogo {
public:
	pii traverse(const std::string& path) const {
		int x = 0;
		int y = 0;
		for (int i : range(path.length())) {
			const int dir = dirs.at(path[i]);
			if (dir == Direction::Unknown) {
				return {INF, INF};
			}
			const int len = (1 << i);
			x += DX[dir] * len;
			y += DY[dir] * len;
		}
		return {x, y};
	}

	void solve(std::istream& in, std::ostream& out) {
		out << "Case #" << ++test_id_ << ": ";
		int n, m;
		in >> n >> m;

		int sum = abs(n) + abs(m);
		if (sum % 2 == 0) {
			out << "IMPOSSIBLE" << std::endl;
			return;
		}

		int step = (1 << (31 - clz(sum)));
		std::string ans;
		while (n != 0 || m != 0) {
			if (abs(n) >= abs(m)) {
				if (n > 0) {
					n -= step;
					ans += 'E';
				} else {
					n += step;
					ans += 'W';
				}
			} else {
				if (m > 0) {
					m -= step;
					ans += 'N';
				} else {
					m += step;
					ans += 'S';
				}
			}
			step /= 2;
		}

		reverse(ans);
		out << ans << std::endl;
	}

	std::string mask_to_path(const int mask) const {
		std::string path;
		int cur = mask;
		while (cur > 0) {
			path += WAYS[cur % 5];
			cur /= 5;
		}
		return path;
	}

	Expogo() {
		// std::cerr << mask_to_path(43) << std::endl;
		for (int mask : range(1 << 0)) {
			std::string path = mask_to_path(mask);
			const pii to = traverse(path);
			if (answers.find(to) == answers.cend()) {
				answers[to] = path;
			}
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}

	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {
		const int MAXN = 40;
		test << MAXN * MAXN * 4 - 1 << std::endl;
		for (int i : inclusiveRange(-MAXN, MAXN)) {
			for (int j : inclusiveRange(-MAXN, MAXN)) {
				if (i == 0 && j == 0) {
					continue;
				}
				test << i << " " << j << std::endl;
			}
		}
	}

private:
	std::unordered_map<pii, std::string> answers;
	size_t test_id_ = 0;
};
