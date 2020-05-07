#include "base/header.hpp"

std::vector<int> find_k_closest(const std::vector<int>& a, size_t K, size_t index) {
	const int element_value = a[index];
	auto right = a.begin() + index;
	std::vector<int>::const_reverse_iterator left(right);
	std::vector<int> result;
	while (result.size() < K) {
		if (left == a.rend()) {
			result.emplace_back(*right);
			++right;
		}
		else if (right == a.cend()) {
			result.emplace_back(*left);
			++left;
		}
		else {
			const int left_value = *left;
			const int right_value = *right;
			if (abs(element_value - left_value) <= abs(element_value - right_value)) {
				result.emplace_back(left_value);
				++left;
			}
			else {
				result.emplace_back(right_value);
				++right;
			}
		}
	}
	return result;
}

class femida8125 {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n, k, index;
		in >> n >> k >> index;
		std::vector<int> a(n);
		in >> a;

		auto ans = find_k_closest(a, k, index);
		sort(ans);
		for (const int x : ans) {
			out << x << " ";
		}
		out << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
