#include "base/header.hpp"
#include "maths/maths.hpp"

class COcherednayaZadachaNaPodschet {
public:
	int solve_slow(int a, int b, int x, int y) const {
		int ans = 0;
		for (int i : inclusiveRange(x, y)) {
			if (i % a % b != i % b % a) {
				++ans;
			}
		}
		return ans;
	}

	void solve(std::istream& in, std::ostream& out) {
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int a, b, q;
			in >> a >> b >> q;
			if (a > b) {
				std::swap(a, b);
			}

			auto cnt = [&a, &b](const ll x) {
				const ll LCM = lcm(a, b);
				return x / LCM * (LCM - b) + std::max(0LL, x % LCM + 1 - b);
			};

//			auto output = [&a, &b, &out](const ll x) {
//				for (ll i : inclusiveRange(1LL, x)) {
//					if (i % a % b != i % b % a) {
//						out << i << " ";
//					}
//				}
//				out << std::endl;
//			};
//
//			output(100);
//			out << solve_slow(a, b, 1, 100) << std::endl;

			for (int query : range(q)) {
				ll l, r;
				in >> l >> r;
				out << cnt(r) - cnt(l - 1) << " ";
			}
			out << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		std::istringstream in(input);
		std::istringstream out(actual_output);

		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int a, b, q;
			in >> a >> b >> q;
			for (int query : range(q)) {
				int x, y;
				in >> x >> y;
				const int jans = solve_slow(a, b, x, y);
				int pans;
				out >> pans;
				if (jans != pans) {
					debug(test_id, query, jans, pans);
					return false;
				}
			}
		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static void generate_test(std::ostream& test) {
		test << 1 << std::endl;
		int a = rand() % 200 + 1;
		int b = rand() % 200 + 1;
		int q = rand() % 10 + 1;
		test << a << " " << b << " " << q << std::endl;
		for (int i : range(q)) {
			int l = rand() % 1000 + 1;
			int r = rand() % 1000 + l;
			test << l << " " << r << std::endl;
		}
	}

private:
	size_t test_id_ = 0;
};
