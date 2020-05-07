#include "base/header.hpp"

const int MOD = 1000000007;
const int MAXN = 111111;

using namespace std;

class BearPasswordLexic {
public:
    /// caide keep
    string findPassword(vector<int> x) {
		const int n = x.size();
		/* int cur_ind = n - 1;
		while (cur_ind >= 0 && x[cur_ind] == 0) {
			--cur_ind;
		}
		if (cur_ind == n - 1) {
			std::string ans(n, 'a');
			return check(ans, x) ? ans : "";
		} */
		std::vector<int> lens;
		int total_sum = 0;
		for (int i = n - 1; i >= 0; --i) {
			const int cur_len = i + 1;
			int cnt = 0;
			for (const auto& it : lens) {
				cnt += max(0, it - cur_len + 1);
			}
			x[i] -= cnt;
			for (int j = 0; j < x[i]; ++j) {
				total_sum += cur_len;
				lens.emplace_back(cur_len);
			}
			if (x[i] < 0 || total_sum > n) {
				return "";
			}
		}
		if (total_sum < n) {
			return "";
		}
		sort(lens, greater<int>());
		int L = 0, R = lens.size();
		string result;
		bool is_a = true;
		while (L < R) {
			if (is_a) {
				result += std::string(lens[L], 'a');
				++L;
			} else {
				--R;
				result += std::string(lens[R], 'b');
			}
			is_a = !is_a;
		}
        return result;
    }

private:
	/* bool check(const std::string& s, const std::vector<int>& cnt) const {
		const int n = s.length();
		for (int i : range(n)) {
			const int len = i + 1;
			int cur_count = 0;
			for (int j : range(0, n - i)) {
				const std::string t = s.substr(i, len);
				if (t.find('a') == std::string::npos || t.find('b') == std::string::npos) {
					++cur_count;
				}
			}
			if (cur_count != cnt[i]) {
				return false;
			}
		}
		return true;
	} */
};


string solve(vector<int> x, int) {
    BearPasswordLexic sol;
    return sol.findPassword(x);
}
