#include "../algolib/cpplib/base/header.hpp"

class DDosugVShkole41 {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int n, k;
		in >> n >> k;
		std::string s;
		in >> s;
		auto is_left = make_vector<bool>(n, false);
		for (int i : range(n)) {
			is_left[i] = (s[i] == 'L');
		}
		std::vector<std::vector<int>> ans;
		bool first = true;
		while (true) {
			ans.emplace_back(std::vector<int>());
			auto& cur_row = ans.back();
			if (first) {
				for (int i : range(1, n)) {
					if (!is_left[i - 1] && is_left[i]) {
						cur_row.emplace_back(i - 1);
					}
				}
				first = false;
			} else {
				const auto& prev_row = ans[ans.size() - 2];
				for (int x : prev_row) {
					if (x > 0 && !is_left[x - 1] && (cur_row.empty() || cur_row.back() != x - 1)) {
						cur_row.emplace_back(x - 1);
					}
					if (x < n - 2 && is_left[x + 2]) {
						cur_row.emplace_back(x + 1);
					}
				}
			}
			if (cur_row.empty()) {
				ans.pop_back();
				break;
			}
			for (auto x : cur_row) {
				is_left[x] = true;
				is_left[x + 1] = false;
			}
		}


		const int min_ans = ans.size();
		int max_ans = 0;
		for (const auto& row : ans) {
			max_ans += row.size();
		}
		if (k < min_ans || k > max_ans) {
			out << -1 << std::endl;
			return;
		}
		int diff = k - min_ans;
		for (const auto& row : ans) {
			const int additional_steps = std::min(static_cast<size_t>(diff), row.size() - 1);
			diff -= additional_steps;
			printf("%d ", (int)row.size() - additional_steps);
			// out << row.size() - additional_steps << " ";
			for (int i : range(row.size() - additional_steps)) {
				printf("%d ", row[i] + 1);
				// out << row[i] + 1 << " ";
			}
			printf("\n");
			// out << std::endl;

			for (int i : inclusiveRange(1, additional_steps)) {
				printf("1 %d\n", row[row.size() - i] + 1);
				// out << "1 " << row[row.size() - i] + 1 << std::endl;
			}
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {
		test << "3000 2250000" << std::endl;
		test << std::string(1500, 'R') << std::string(1500, 'L') << std::endl;
	}

private:
	size_t test_id_ = 0;
};
