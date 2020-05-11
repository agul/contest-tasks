#include "base/header.hpp"
#include "string/utils.hpp"

class FVosstanovlenie01Stroki {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int a, b, c;
			in >> a >> b >> c;
			std::string ans;
			if (a > 0) {
				ans.assign(a + 1, '0');
			}
			bool add_zero = false;
			if (b % 2 == 0 && b > 0) {
				add_zero = true;
				--b;
			}
			if (b > 0) {
				if (ans.empty()) {
					ans = "0";
				}
				for (int i : range(b)) {
					ans += '0' + to_digit(ans.back()) ^ 1;
				}
			}
			if (c > 0) {
				if (ans.empty()) {
					ans = "1";
				}
				ans += std::string(c, '1');
			}
			if (add_zero) {
				ans += '0';
			}
			out << ans << std::endl;
		}
	}

	static std::tuple<int, int, int> calc(const std::string& s) {
		int pa = 0;
		int pb = 0;
		int pc = 0;
		for (int i : range(1, (int)s.length())) {
			if (s[i] != s[i - 1]) {
				++pb;
			} else {
				if (s[i] == '1') {
					++pc;
				} else {
					++pa;
				}
			}
		}
		return {pa, pb, pc};
	}

	static constexpr bool kUseCustomChecker = true;
	bool check(std::string input, std::string expected_output, std::string actual_output) {
		std::istringstream in(input);
		std::istringstream participant(actual_output);
		int tests_count;
		in >> tests_count;
		for (int test : range(tests_count)) {
			int a, b, c;
			in >> a >> b >> c;
			int pa = 0;
			int pb = 0;
			int pc = 0;
			std::string pans;
			participant >> pans;
			std::tie(pa, pb, pc) = calc(pans);
			if (pa != a || b != pb || c != pc) {
				debug(a, b, c);
				debug(pa, pb, pc);
				std::cerr << "FAIL at test case " << test + 1 << std::endl;
				return false;
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1;
	static void generate_test(std::ostream& test) {
		const int kTestsCount = 1000;
		const int kMaxLen = 1000;
		test << kTestsCount << std::endl;
		for (int i : range(kTestsCount)) {
			std::string cur;
			int len = Random::get(kMaxLen) + 2;
			for (int j : range(len)) {
				cur += '0' + Random::get(2);
			}
			int a, b, c;
			std::tie(a, b, c) = calc(cur);
			test << a << " " << b << " " << c << std::endl;
		}
	}

private:
	size_t test_id_ = 0;
};
