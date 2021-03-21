#include "base/header.hpp"

class CModniiNomer {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        std::string s;
        in >> n >> k >> s;

        std::vector<std::vector<int>> positions(10);

        for (int i : range(n)) {
            const int digit = s[i] - '0';
            positions[digit].emplace_back(i);
        }

        int cur_best = INF;
        std::vector<std::string> variants;
        for (int digit : range(10)) {
            int add = std::max<int>(0, k - positions[digit].size());
            std::string tmp = s;
            int cur_ans = 0;
            for (int delta : range(1, 10)) {
                for (int mul : inclusiveDownrange(1, -1)) {
                    if (add == 0) {
                        break;
                    }
                    const int digit_to_change = digit + mul * delta;
                    if (mul == 0 || digit_to_change < 0 || digit_to_change > 9) {
                        continue;
                    }
                    if (digit_to_change > digit) {
                        for (const int pos : positions[digit_to_change]) {
                            if (add == 0) {
                                break;
                            }
                            --add;
                            cur_ans += delta;
                            tmp[pos] = digit + '0';
                        }
                    } else {
                        for (const int pos : reversed(positions[digit_to_change])) {
                            if (add == 0) {
                                break;
                            }
                            --add;
                            cur_ans += delta;
                            tmp[pos] = digit + '0';
                        }
                    }
                }
            }
            if (umin(cur_best, cur_ans)) {
                variants = {tmp};
                debug(tmp);
            }
            else if (cur_best == cur_ans) {
                variants.emplace_back(tmp);
            }
        }

        out << cur_best << std::endl;
        out << *min_element(variants) << std::endl;
	}


	CModniiNomer() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
