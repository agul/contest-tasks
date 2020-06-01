#include "base/header.hpp"
#include "collections/queue/queue.hpp"

class BOdnopolyusnieMagniti {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		std::vector<std::string> field(n);
		in >> field;

		auto color = make_vector<bool>(n, m, false);
		for (int i : range(n)) {
			for (int j : range(m)) {
				color[i][j] = (field[i][j] == '#');
			}
		}
		auto used = make_vector<bool>(n, m, false);
		auto row_black = make_vector<bool>(n, false);
		auto col_black = make_vector<bool>(m, false);
		auto row_white = make_vector<bool>(n, false);
		auto col_white = make_vector<bool>(m, false);

		int cnt = 0;
		bool ok = true;

		Queue<pii> q(n * m);

		for (int i : range(n)) {
			for (int j : range(m)) {
				if (!color[i][j]) {
					if (row_black[i]) {
						row_white[i] = true;
					}
					if (col_black[j]) {
						col_white[j] = true;
					}
					continue;
				}

				if (row_white[i] || col_white[j]) {
					ok = false;
					break;
				}
				row_black[i] = true;
				col_black[j] = true;

				if (used[i][j]) {
					continue;
				}
				++cnt;

				q.clear();
				q.push({i, j});
				used[i][j] = true;
				while (!q.empty()) {
					int curX, curY;
					std::tie(curX, curY) = q.pop_front();

					for (int dir : range(4)) {
						const int newX = curX + DX[dir];
						const int newY = curY + DY[dir];
						if (newX < 0 || newX >= n || newY < 0 || newY >= m || used[newX][newY] || !color[newX][newY]) {
							continue;
						}
						q.push({newX, newY});
						used[newX][newY] = true;
					}

				}

			}
			if (!ok) {
				break;
			}
		}

		bool any_free_row = false;
		bool any_free_col = false;
		for (int i : range(n)) {
			any_free_row |= !row_black[i];
		}
		for (int i : range(m)) {
			any_free_col |= !col_black[i];
		}

		ok &= !(any_free_col ^ any_free_row);

		if (!ok) {
			out << -1 << std::endl;
			return;
		}
		out << cnt << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
