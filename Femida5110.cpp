#include "../algolib/cpplib/base/header.hpp"

class Femida5110 {
public:
	bool try_swap(std::vector<int>& a, const size_t x, const size_t y) {
		std::swap(a[x], a[y]);
		bool is_sorted = true;
		for (size_t i = 1; i < a.size(); ++i) {
			is_sorted &= (a[i] >= a[i - 1]);
		}
		std::swap(a[x], a[y]);
		return is_sorted;
	}

	bool sort_by_one_swap(const std::vector<int>& vec) {
		auto a = vec;

		size_t pos_first = 0;
		size_t pos_second = 0;
		for (size_t i = 1; i < vec.size(); ++i) {
			if (a[i] < a[i - 1]) {
				if (pos_first == 0) {
					pos_first = i;
				}
				else if (pos_second == 0) {
					pos_second = i;
				}
				else {
					return false;
				}
			}
		}

		if (pos_first == 0) {
			return true;
		}
		if (pos_second == 0) {
			return try_swap(a, pos_first - 1, pos_first);
		}
		return try_swap(a, pos_first - 1, pos_second - 1)
		       || try_swap(a, pos_first, pos_second - 1)
		       || try_swap(a, pos_first - 1, pos_second)
		       || try_swap(a, pos_first, pos_second);
	}

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		auto a = make_vector<int>(n, 0);
		in >> a;
		out << std::boolalpha << sort_by_one_swap(a) << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
