#include "base/header.hpp"

class BPodposledovatelnostiCodeforces {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		ll n;
		in >> n;

		const std::string codeforces = "codeforces";

		if (n == 1) {
			out << codeforces << std::endl;
			return;
		}

		auto pow10 = [](const int n) {
			ll res = 1;
			for (int i : range(10)) {
				res *= n;
			}
			return res;
		};

		int deg = 1;
		while (pow10(deg) < n) {
			++deg;
		}

		std::vector<int> ans(10, deg - 1);
		ll cur_res = pow10(deg - 1);
		int cnt = 0;
		while (cur_res < n) {
			cur_res /= deg - 1;
			cur_res *= deg;
			++cnt;
		}
		for (int i : range(cnt)) {
			++ans[i];
		}

		std::string res;
		for (int i : range(10)) {
			res += std::string(ans[i], codeforces[i]);
		}
		out << res << std::endl;
	}


	BPodposledovatelnostiCodeforces() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
