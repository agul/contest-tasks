#include "base/header.hpp"
#include "maths/maths.hpp"

int calculate(const std::vector<std::string>& field) {
	std::unordered_set<int> sums;
	const int n = field.size();
	for (int i : range(n)) {
		int cur_sum = 0;
		for (int j : range(n)) {
			cur_sum += field[i][j] - '0';
		}
		sums.emplace(cur_sum);
	}
	for (int j : range(n)) {
		int cur_sum = 0;
		for (int i : range(n)) {
			cur_sum += field[i][j] - '0';
		}
		sums.emplace(cur_sum);
	}
	return sums.size();
}

const int VALS[] = {0, 1, 4, 5};

std::vector<std::string> solve_slow(const int n) {
	std::vector<std::string> a(n, std::string(n, '0'));

	int X = sqr(n);
	int MASK = pow(3, X);

	auto best = a;
	int ans = 0;

	for (int mask : range(MASK)) {
		int cur = mask;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				a[i][j] = '0' + cur % 3;
				cur /= 3;
			}
		}
		const int cur_value = calculate(a);
		if (umax(ans, cur_value)) {
			best = a;
		}
		if (cur_value == VALS[n]) {
			for (const auto& it: a) {
				std::cout << it << std::endl;
			}
			std::cout << "-------" << std::endl;
		}
	}
	return best;
}

class TAASquares {
public:
	std::vector <std::string> construct(int n) {
		return solve_slow(n);
	}
};

class SRM784_hard {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		TAASquares solution;
		auto ans = solution.construct(n);
		for (const auto& it : ans) {
			out << it << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		std::istringstream in(input);
		std::istringstream jury(expected_output);
		std::istringstream participant(actual_output);

		int n;
		in >> n;

		auto j = make_vector<std::string>(n, "");
		auto p = make_vector<std::string>(n, "");

		jury >> j;
		participant >> p;

		const int j_ans = calculate(j);
		const int p_ans = calculate(p);
		debug(input, j_ans, p_ans);
		return j_ans == p_ans;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
