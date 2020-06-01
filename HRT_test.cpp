#include "base/header.hpp"

class HRT_test {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		std::vector<int> a(n);
		std::vector<int> b(m);
		in >> a >> b;

		if (a.size() < b.size()) {
			a.swap(b);
		}
		std::vector<int> result;
		result.reserve(a.size() + 2);
		int carry = 0;
		for (size_t i = 0; i < a.size() || carry != 0; ++i) {
			const int a_bit = (i < a.size() ? a[i] : 0);
			const int b_bit = (i < b.size() ? b[i] : 0);
			const int cur_bit = a_bit + b_bit - carry;
			if (cur_bit == -1) {
				result.emplace_back(1);
				carry = -1;
			} else {
				result.emplace_back(cur_bit % 2);
				carry = cur_bit / 2;
			}
		}
		while (!result.empty() && result.back() == 0) {
			result.pop_back();
		}
		out << result.size() << std::endl;
		for (int x : result) {
			out << x << " ";
		}
		out << std::endl;
	}


	HRT_test() {}

	static ll vec_to_int(const std::vector<int>& a) {
		const int kBase = -2;
		ll res = 0;
		ll degree = 1;
		for (int x : a) {
			res += x * degree;
			degree *= kBase;
		}
		return res;
	}

	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n, m;
		in >> n >> m;
		std::vector<int> a(n);
		std::vector<int> b(m);
		in >> a >> b;

		int k;
		out >> k;
		std::vector<int> c(k);
		out >> c;

		const ll value_a = vec_to_int(a);
		const ll value_b = vec_to_int(b);
		const ll value_c = vec_to_int(c);

		if (c.back() == 0) {
			debug("REMOVE zeroes", c);
			return false;
		}

		if (value_a + value_b != value_c) {
			debug(value_a, value_b, value_c);
			return false;
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 30;
		const int n = Random::get(1, kMaxn);
		const int m = Random::get(1, kMaxn);
		std::vector<int> a(n - 1);
		std::vector<int> b(m - 1);
		for (int& x : a) {
			x = Random::get(0, 1);
		}
		for (int& x : b) {
			x = Random::get(0, 1);
		}
		a.emplace_back(1);
		b.emplace_back(1);
		test << n << " " << m << std::endl;
		for (int x : a) {
			test << x << " ";
		}
		test << std::endl;
		for (int x : b) {
			test << x << " ";
		}
		test << std::endl;
	}

};
