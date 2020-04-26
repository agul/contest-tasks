#include "../algolib/cpplib/base/header.hpp"

class Femida7301 {
public:
	struct Letter {
		size_t last_block_start_;
		size_t last_block_cnt_;
		size_t total_cnt_;
		char symbol_;
	};

	size_t find_max_substring(const std::string& s) {
		if (s.empty()) {
			return 0;
		}
		Letter cur{0, 1, 1, s.front()};
		Letter prev{0, 0, 0, 0};
		size_t ans = 1;
		for (size_t i = 1; i < s.length(); ++i) {
			const char ch = s[i];
			if (ch == cur.symbol_) {
				++cur.last_block_cnt_;
				++cur.total_cnt_;
			} else {
				std::swap(prev, cur);
				if (ch != cur.symbol_) {
					cur.total_cnt_ = 0;
					prev.total_cnt_ =  prev.last_block_cnt_;
				}
				cur.symbol_ = ch;
				cur.last_block_start_ = i;
				cur.last_block_cnt_ = 1;
				++cur.total_cnt_;
			}
			ans = std::max(ans, cur.total_cnt_ + prev.total_cnt_);
		}
		return ans;
	}

	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		in >> s;
		out << find_max_substring(s) << std::endl;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
