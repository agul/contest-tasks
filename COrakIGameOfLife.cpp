#include "base/header.hpp"
#include "collections/queue/queue.hpp"

class COrakIGameOfLife {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m, t;
		in >> n >> m >> t;
		std::vector<std::string> field(n);
		in >> field;

		auto get_cell = [&field, n, m](const int x, const int y) {
			if (x < 0 || y < 0 || x >= n || y >= m) {
				return -1;
			}
			return field[x][y] - '0';
		};

		auto time = make_vector<ll>(n, m, LINF);
		Queue<pii> q(n * m);

		for (int i : range(n)) {
			for (int j : range(m)) {
				const int cell_value = get_cell(i, j);
				bool any = false;
				for (int dir : range(4)) {
					const int cell = get_cell(i + DX[dir], j + DY[dir]);
					any |= (cell == cell_value);
				}
				if (any) {
					q.push({i, j});
					time[i][j] = 0;
				}
			}
		}

		while (!q.empty()) {
			int x, y;
			std::tie(x, y) = q.pop_front();
			const ll cur_time = time[x][y];
			const int cell_value = get_cell(x, y) ^ 1;
			for (int dir : range(4)) {
				const int nx = x + DX[dir];
				const int ny = y + DY[dir];
				const int cell = get_cell(nx, ny);
				if (cell == -1) {
					continue;
				}
				if (cell == cell_value && umin(time[nx][ny], cur_time + 1)) {
					q.push({nx, ny});
				}
			}
		}

		for (int query : range(t)) {
			int x, y;
			ll p;
			in >> x >> y >> p;
			--x;
			--y;
			// --p;

			const int cell = get_cell(x, y);

			if (p < time[x][y]) {
				out << cell << std::endl;
				continue;
			}

			p -= time[x][y];
			p &= 1;
			out << (cell ^ p) << std::endl;
		}
	}


	COrakIGameOfLife() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		/* int x, y, t;
		in >> x >> y >> t;
		for (int i : range(t)) {
			int pans;
			int jans;
			out >> pans;
			jury >> jans;
			if (pans != jans) {
				debug(i + 1, pans, jans);
				return false;
			}
		} */

		int n, m, t;
		in >> n >> m >> t;
		std::vector<std::string> field(n);
		in >> field;

		auto get_cell = [&field, n, m](const int x, const int y) {
			if (x < 0 || y < 0 || x >= n || y >= m) {
				return -1;
			}
			return static_cast<int>(field[x][y]);
		};

		using Ans = std::pair<pii, int>;

		std::vector<std::string> new_field;
		std::map<Ans, int> answers;
		for (int iter : range(1000)) {
			new_field = field;
			for (int i : range(n)) {
				for (int j : range(m)) {
					const int cell_value = get_cell(i, j);
					bool any = false;
					for (int dir : range(4)) {
						const int cell = get_cell(i + DX[dir], j + DY[dir]);
						any |= (cell == cell_value);
					}
					if (any) {
						new_field[i][j] = cell_value ^ 1;
					}
					answers.emplace(Ans{pii{i, j}, iter + 1}, (int)new_field[i][j] - '0');
				}
			}
			field.swap(new_field);
		}

		for (int i : range(t)) {
			int x, y, p;
			in >> x >> y >> p;
			int pans;
			out >> pans;
			const auto it = answers.find(Ans{pii{x - 1, y - 1}, p});
			if (it == answers.cend()) {
				debug("WTF");
				return false;
			}
			const int jans = it->second;
			if (pans != jans) {
				debug(x, y, p, pans, jans);
				return false;
			}

		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 20;

		const int n = Random::get(1, kMaxn);
		const int m = Random::get(1, kMaxn);
		std::vector<std::string> field(n, std::string(m, '0'));
		test << n << " " << m << " 0" << std::endl;

		if (Random::get(0, 2) == 0) {
			for (int i : range(n)) {
				for(int j : range(m)) {
					field[i][j] = (i + j) % 2 + '0';
				}
			}
			int changes = Random::get(1, 1);
			for (int i : range(changes)) {
				int x = Random::get(0, n -1);
				int y = Random::get(0, m - 1);
				field[x][y] ^= 1;
			}
		} else {
			for (int i : range(n)) {
				for(int j : range(m)) {
					field[i][j] = '0' + Random::get(0, 1);
				}
			}
		}


		for (const auto& row : field) {
			test << row << std::endl;
		}
	}

};
