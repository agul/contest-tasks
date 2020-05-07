#include "Head.h"

const int MOD = 1000000007;
const int MAXN = 111111;


class ReplacingDigit {
public:
    /// caide keep
    int getMaximumStockWorth(std::vector<int> prices, std::vector<int> stickers) {
		std::vector<std::string> p;
		for (const auto& price : prices) {
			p.emplace_back(std::to_string(price));
		}
		for (int i = 8; i >= 0; --i) {
			int digit = i + 1;
			char char_digit = digit + '0';
			for (int j = 0; j < stickers[i]; ++j) {
				int max_diff = 0;
				int ind = -1;
				std::string best;
				for (int k = 0; k < p.size(); ++k) {
					const auto& it = p[k];
					std::string s = it;
					int val = std::stoi(it);
					for (auto& ch : s) {
						std::swap(ch, char_digit);
						int new_val = std::stoi(s);
						if (umax(max_diff, new_val - val)) {
							ind = k;
							best = s;
						}
						std::swap(ch, char_digit);
					}
				}
				if (max_diff == 0) {
					continue;
				}
				p[ind] = best;
			}
		}
		int result = 0;
		for (const auto& price : p) {
			result += std::stoi(price);
		}
        return result;
    }
};


int solve(std::vector<int> A, std::vector<int> D, int) {
    ReplacingDigit sol;
    return sol.getMaximumStockWorth(A, D);
}
