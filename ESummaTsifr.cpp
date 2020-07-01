#include "base/header.hpp"

class ESummaTsifr {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		out << ans[n][k] << std::endl;

//		for (int i : range(kMaxn + 1)) {
//			for (int j : range(kMaxk + 1)) {
//				if (ans[i][j] == -1) {
//					out << i << " " << j << std::endl;
//				}
//			}
//		}
	}

	const int kMaxn = 150;
	const int kMaxk = 9;
	std::vector<std::vector<ll>> ans;

	const int kMaxM = 1111111;

	static ll get_ans_k_0(int n) {
		int cnt = 0;
		while (n > 9) {
			n -= 9;
			++cnt;
		}
		return std::stoll(std::string(1, n + '0') + std::string(cnt, '9'));
	}

	ESummaTsifr() {
		ans = make_vector<ll>(kMaxn + 1, kMaxk + 1, -1);

		for (int i : inclusiveRange(1, kMaxn)) {
			ans[i][0] = get_ans_k_0(i);
		}

		ll current_ans = 9;
		ll step = 10;
		int cnt = 0;
		for (int i : inclusiveRange(3, kMaxn)) {
			if (i % 2 == 1) {
				ans[i][1] = get_ans_k_0((i + 1) / 2) - 1;
				continue;
			}
			if (i < 10) {
				continue;
			}
			ans[i][1] = current_ans;
			++cnt;
			if (cnt == 9) {
				cnt = 0;
				step *= 10;
			}
			current_ans += step;
		}

		for (int i : range(kMaxM)) {
			int sum = 0;
			for (int j : inclusiveRange(kMaxk)) {
				int value = i + j;
				int cur_sum = 0;
				while (value > 0) {
					cur_sum += value % 10;
					value /= 10;
				}
				sum += cur_sum;
				if (sum > kMaxn) {
					break;
				}
				if (ans[sum][j] == -1) {
					ans[sum][j] = i;
				}
			}
		}
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
