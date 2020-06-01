#include "base/header.hpp"

class CObnovlenieCelex {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;


	std::vector<std::vector<int>> a;
	std::vector<int> sums;

	void go(int x, int y, int n, int m, int sum) {
		// debug(x, y, n, m);
		if (x > n || y > m) {
			return;
		}
		sum += a[x][y];
		if (x == n && y == m) {
			sums.emplace_back(sum);
			return;
		}
		go(x + 1, y, n, m, sum);
		go(x, y + 1, n, m, sum);
	}

	void solve(std::istream& in, std::ostream& out) {

		ll x1, y1, x2, y2;
		in >> x1 >> y1 >> x2 >> y2;
		out << (y2 - y1) * (x2 - x1) + 1 << std::endl;
		return;

		a = make_vector<int>(10, 10, 0);
		int value = 0;
		for (int i : range(10)) {
			for (int j : inclusiveRange(i)) {
				a[j][i - j] = value++;
			}
		}

		auto ans = make_vector<int>(10, 10, 0);
		for (int i : range(10)) {
			for (int j : range(10)) {
				sums.clear();
				go(0, 0, i, j, 0);
				dedup(sums);
				ans[i][j] = sums.size();
			}
		}

		for (const auto& row : ans) {
			for (const auto& cell : row) {
				out << std::setw(5) << cell;
			}
			out << std::endl;
		}


	}


	CObnovlenieCelex() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
