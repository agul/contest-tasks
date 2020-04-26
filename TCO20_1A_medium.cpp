#include "../algolib/cpplib/base/header.hpp"

size_t test_id_ = 0;

class TCO20_1A_medium {
public:
	std::vector <std::string> construct_true(int N) {
		int cnt_blocks = (N - 1) / 48 + 1;
		std::vector<std::string> ans;
		std::string empty_row(50, '.');
		std::string alive_row(50, 'X');
		for (int i = 0; i < cnt_blocks; ++i) {
			if (i & 1) {
				ans.emplace_back(alive_row);
				ans.emplace_back(empty_row);
			} else {
				ans.emplace_back(empty_row);
				ans.emplace_back(alive_row);
			}
		}
		const int last_block_cnt = N - (cnt_blocks - 1) * 48;
		for (int i = last_block_cnt + 2; i < 50; ++i) {
			ans[0][i] = 'X';
		}
		return ans;
	}

	std::vector <std::string> construct(int n) {
		std::vector<std::string> ans(50, std::string(50, '.'));
		int r = 1;
		while (n > 1) {
			for (int i : range(48)) {
				ans[r][0] = ans[r][1] = 'X';
				ans[r][i + 2] = 'X';
				n -= 1;
				if (n == 0) {
					break;
				}
			}
			r += 3;
		}
//		if (n == 1) {
//			ans[49][49] = 'X';
//			ans[48][49] = 'X';
//			ans[49][48] = 'X';
//		}
		return ans;
	}

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		auto ans = construct(n);

		out << ans.size() << " " << ans.front().size() << std::endl;
		for (auto x : ans) {
			out << x << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		int n;
		std::istringstream in(input);
		std::istringstream out(actual_output);
		in >> n;

		int m, k;
		out >> m >> k;
		std::vector<std::string> a(m);
		out >> a;

		if (m > 50 || k > 50) {
			return false;
		}

		int cnt = 0;
		for (int i : range(m)) {
			for (int j : range(k)) {
				if (a[i].size() != k) {
					return false;
				}
				int cur_cnt = 0;
				for (int dir : range(8)) {
					int nx = i + DX[dir];
					int ny = j + DY[dir];
					if (nx < 0 || ny < 0 || nx >= m || ny >= k) {
						continue;
					}
					if (a[nx][ny] == 'X') {
						++cur_cnt;
					}
				}
				if (a[i][j] == '.' && cur_cnt == 3) {
					++cnt;
				}
			}
		}

		std::cerr << "Received " << cnt << " cells, expected = " << n << std::endl;

		return cnt == n;
	}


	static constexpr size_t kGeneratedTestsCount = 500;
	static void generate_test(std::ostream& test) {
		test << ++test_id_ << std::endl;
	}

private:
};
