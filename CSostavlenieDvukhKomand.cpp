#include "../algolib/cpplib/base/header.hpp"

class CSostavlenieDvukhKomand {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;
			SafeUnorderedMap<int, int> cnt;
			for (int x : a) {
				cnt[x] += 1;
			}
			const int diff = cnt.size();
			int ans = 0;
			for (const auto& it : cnt) {
				const int x = std::min(diff, it.second - 1);
				const int y = std::min(diff - 1, it.second);
				umax(ans, std::max(x, y));
			}
			out << ans << std::endl;
		}
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
