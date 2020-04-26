#include "../algolib/cpplib/base/header.hpp"

class PascalWalk {
public:
	void solve(std::istream& in, std::ostream& out) {
		out << "Case #" << ++test_id_ << ": " << std::endl;

		ll n;
		in >> n;

		const int bits = 32 - __builtin_clz(n);
		const int cur = n - bits;

		int value = 0;
		int x = 0;
		int y = 0;
		std::vector<pii> ans;
		for (int i : range(bits)) {
			if (cur & (1 << i)) {
				value += sum[x];
				if (y == 0) {
					for (int j : inclusiveRange(i)) {
						ans.emplace_back(x, j);
					}
					++x;
					y = x;
				} else {
					for (int j : inclusiveDownrange(i)) {
						ans.emplace_back(x, j);
					}
					++x;
					y = 0;
				}
			} else {
				value += 1;
				ans.emplace_back(x, y);
				if (x == y) {
					++y;
				}
				++x;
			}
		}

		for (int i : range(n - value)) {
			ans.emplace_back(x, y);
			++x;
			if (y != 0) {
				++y;
			}
		}

		for (const auto& x : ans) {
			out << x.first + 1 << " " << x.second + 1 << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		std::istringstream in(input);
		std::istringstream output(actual_output);

		in >> std::ws;


		ll a[64][64];

		fill(a, 0);
		a[0][0] = 1;
		for (int i : range(63)) {
			for (int j : inclusiveRange(i)) {
				a[i + 1][j] += a[i][j];
				a[i + 1][j + 1] += a[i][j];
			}
		}

		int testsCount;
		in >> testsCount;
		bool ok = true;
		for (int test : range(testsCount)) {
			std::string case_num;
			std::getline(output, case_num);
			bool visited[64][64];
			fill(visited, false);
			ll sum = 0;
			while (output.peek() != 'C' && !output.eof()) {
				std::string output_line;
				std::getline(output, output_line);

				int x, y;
				std::istringstream pair(output_line);
				pair >> x >> y;

				--x;
				--y;
				sum += a[x][y];
				if (visited[x][y] || x < 0 || y > x || y < 0) {
					std::cout << "FAIL " << x + 1 << " " << y + 1 << std::endl;
					return false;
				}
				visited[x][y] = true;
			}
			ll N;
			in >> N;
			ok &= (sum == N);
			// std::cout << "### " << sum << " " << N << std::endl;
		}
		return ok;
	}

	PascalWalk() {
		fill(a, 0);
		fill(sum, 0);
		a[0][0] = 1;
		for (int i : range(63)) {
			for (int j : inclusiveRange(i)) {
				a[i + 1][j] += a[i][j];
				a[i + 1][j + 1] += a[i][j];
				sum[i] += a[i][j];
			}
		}
	}

private:
	size_t test_id_ = 0;
	ll a[64][64];
	ll sum[64];
};
