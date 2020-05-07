#include "base/header.hpp"

class BFeniksIKrasota {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n, k;
			in >> n >> k;
			auto a = make_vector<int>(n, 0);
			in >> a;

			std::unordered_map<int, int> digits_pos;
			std::vector<int> digits;
			for (int i : range(n)) {
				const int val = a[i];
				if (digits_pos.find(val) == digits_pos.cend()) {
					digits_pos[val] = digits.size();
					digits.emplace_back(val);
				}
			}

			if (k < digits.size()) {
				out << -1 << std::endl;
				continue;
			}

			int cur_digit = 0;
			while (digits.size() < k) {
				++cur_digit;
				if (digits_pos.find(cur_digit) == digits_pos.cend()) {
					digits_pos[cur_digit] = digits.size();
					digits.emplace_back(cur_digit);
				}
			}

			for (int& x : a) {
				x = digits_pos[x];
			}

			std::vector<int> ans;
			std::vector<bool> used(n + 1, false);

			int cnt = 0;

			auto pop = [&ans, &used, k, &cnt]() {
				if (cnt < k) {
					return false;
				}
				used[ans[ans.size() - k]] = false;
				--cnt;
				return true;
			};

			auto add_to_ans = [&ans, &used, &pop, &cnt](const int val) {
				pop();
				assert(!used[val]);
				used[val] = true;
				ans.emplace_back(val);
				++cnt;
			};

			int last = 0;
			int index = 0;
			while (index < n) {
				pop();
				const int x = a[index];
				if (used[x]) {
					for (int cur : range(k)) {
						if (!used[cur]) {
							add_to_ans(cur);
						}
					}
					continue;
				}
				add_to_ans(x);
				++index;
			}

			// debug(ans);

			out << ans.size() << std::endl;
			for (int x : ans) {
				out << digits[x] << " ";
			}
			out << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
