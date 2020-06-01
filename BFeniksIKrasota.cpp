#include "base/header.hpp"
#include "collections/value_compressor.hpp"

class BFeniksIKrasota {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n, k;
			in >> n >> k;
			auto a = make_vector<int>(n, 0);
			in >> a;

			auto digits = IntegralValueCompressor<int>(a);
			debug(digits);

			if (k < digits.size()) {
				out << -1 << std::endl;
				continue;
			}

			int cur_digit = 0;
			while (digits.size() < k) {
				++cur_digit;
				digits.add(cur_digit);
			}

			debug(digits);

			for (int& x : a) {
				x = digits[x];
			}

			debug(a);

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
				out << digits.get_by_id(x) << " ";
			}
			out << std::endl;
		}
	}

	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
