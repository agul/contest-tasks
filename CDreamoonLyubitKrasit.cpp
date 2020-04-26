#include "../algolib/cpplib/base/header.hpp"

class CDreamoonLyubitKrasit {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int n, m;
		in >> n >> m;
		std::vector<ll> operations(m);
		in >> operations;

		std::vector<ll> ans(m);
		ll sum = 0;
		for (int i : range(m)) {
			const int cur_len = operations[i];
			const int rightmost_pos = n - cur_len;
			if (rightmost_pos < i) {
				out << -1 << std::endl;
				return;
			}
			ans[i] = sum;
			sum += cur_len;
		}
		if (sum < n) {
			out << -1 << std::endl;
			return;
		}

		sum -= n;
		ll diff = 0;
		for (int i : range(1, m)) {
			const int len = operations[i];

			ans[i] -= diff;
			const int new_diff = std::min(sum, ans[i] - i);
			ans[i] -= new_diff;
			sum -= new_diff;
			diff += new_diff;
		}


		for (ll x : ans) {
			out << x + 1 << " ";
		}
		out << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
		std::istringstream in(input);
		std::istringstream out(actual_output);

		int n, m;
		in >> n >> m;

		out >> std::skipws;
		if (out.peek() == '-') {
			return false;
		}

		std::vector<int> op(m), ans(m);
		in >> op;
		out >> ans;

		std::vector<int> state(n, -1);
		for (int pos : ans) {

		}

		return true;
	}

	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {

	}

private:
	size_t test_id_ = 0;
};
