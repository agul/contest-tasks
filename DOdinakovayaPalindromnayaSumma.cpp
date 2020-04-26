#include "../algolib/cpplib/base/header.hpp"

class DOdinakovayaPalindromnayaSumma {
public:
	void solve(std::istream& in, std::ostream& out) {
		int tests_count;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int m, k;
			in >> m >> k;
			auto a = make_vector<int>(m, 0);
			in >> a;
			SafeUnorderedMultiSet<int> cnt;
			std::vector<pii> mins, maxs;
			for (int i : range(m / 2)) {
				const int x = a[i];
				const int y = a[m - i - 1];
				const int cur_sum = x + y;
				mins.emplace_back(std::min(x, y), cur_sum);
				maxs.emplace_back(std::max(x, y), cur_sum);
			}
			const int n = mins.size();
			sort(mins);
			sort(maxs);
			int min_ind = 0;
			int max_ind = 0;
			int ans = INF;
			debug(mins);
			debug(maxs);
			for (int sum : inclusiveRange(2, k * 2)) {
				debug(sum);
				while (min_ind < n && mins[min_ind].first < sum) {
					cnt.emplace(mins[min_ind].second);
					++min_ind;
				}
				while (max_ind < n && maxs[max_ind].first < sum - k) {
					auto it = cnt.find(maxs[max_ind].second);
					assert(it != cnt.cend());
					cnt.erase(it);
					++max_ind;
				}
				debug(min_ind, max_ind);
				const int neq_sum_cnt = cnt.size() - cnt.count(sum);
				const int cur = (n - min_ind) * 2 + max_ind * 2 + neq_sum_cnt;
				debug(n - min_ind, max_ind, neq_sum_cnt);
				umin(ans, cur);
				debug("--------");
			}
			out << ans << std::endl;
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
