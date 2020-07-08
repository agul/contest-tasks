#include "base/header.hpp"

class BTablitsaSosedei {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		auto a = make_vector<int>(n, m, 0);
		in >> a;

		auto count_neighbours = [&a, n, m](const int x, const int y, const int value) {
			int cnt = 0;
			for (int dir : range(4)) {
				const int nx = x + DX[dir];
				const int ny = y + DY[dir];
				if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
					continue;
				}
				if (value == -1) {
					++cnt;
				}
				if (value == 0 && a[nx][ny] == 0) {
					++cnt;
				}
				if (value > 0 && a[nx][ny] > 0) {
					++cnt;
				}
			}
			return cnt;
		};

		auto ans = a;
		for (int i : range(n)) {
			for (int j : range(m)) {
				if (a[i][j] > count_neighbours(i, j, -1)) {
					out << "NO" << std::endl;
					return;
				}
				if (a[i][j] == 0) {
					continue;
				}
				int more_zero = count_neighbours(i, j, 1);
				debug(i, j, more_zero);
				if (more_zero > a[i][j]) {
					ans[i][j] = more_zero;
				}
				if (more_zero < a[i][j]) {
					for (int dir : range(4)) {
						const int nx = i + DX[dir];
						const int ny = j + DY[dir];
						if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
							continue;
						}
						if (a[nx][ny] == 0) {
							++ans[nx][ny];
							++more_zero;
							if (more_zero == a[i][j]) {
								break;
							}
						}

					}
				}
			}
		}

		a = ans;
		for (int i : range(n)) {
			for (int j : range(m)) {
				if (ans[i][j] != 0) {
					ans[i][j] = count_neighbours(i, j, 1);
				}
			}
		}

		out << "YES" << std::endl;
		for (int i : range(n)) {
			for (int j : range(m)) {
				out << ans[i][j] << " ";
			}
			out << std::endl;
		}
	}


	BTablitsaSosedei() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount;
		in >> testsCount;
		for (int testid : range(testsCount)) {
			int n, m;
			in >> n >> m;
			auto a = make_vector<int>(n, m, 0);
			in >> a;
			std::string pans;
			out >> pans;
			if (pans == "NO") {
				continue;
			}
			out >> a;

			debug(a);


			auto count_neighbours = [&a, n, m](const int x, const int y, const int value) {
				int cnt = 0;
				for (int dir : range(4)) {
					const int nx = x + DX[dir];
					const int ny = y + DY[dir];
					if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
						continue;
					}
					if (value == -1) {
						++cnt;
					}
					if (value == 0 && a[nx][ny] == 0) {
						++cnt;
					}
					if (value > 0 && a[nx][ny] > 0) {
						++cnt;
					}
				}
				return cnt;
			};

			for (int i : range(n)) {
				for (int j : range(m)) {
					if (a[i][j] == 0) {
						continue;
					}
					if (count_neighbours(i, j, 1) != a[i][j]) {
						debug(testid, i, j);
						return false;
					}
				}
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
