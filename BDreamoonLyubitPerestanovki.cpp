#include "../algolib/cpplib/base/header.hpp"

class BDreamoonLyubitPerestanovki {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		int tests_count = 0;
		in >> tests_count;
		for (int test_id : range(tests_count)) {
			int n;
			in >> n;
			auto a = make_vector<int>(n, 0);
			in >> a;
			std::multiset<int> x = {};
			std::multiset<int> y(all(a));

			std::set<int> xx;
			std::set<int> yy(all(a));
			std::vector<pii> ans;
			for (int cur : a) {
				x.emplace(cur);
				xx.emplace(cur);
				y.erase(y.find(cur));
				if (y.count(cur) == 0) {
					yy.erase(cur);
				}
				if (check_set(x, xx) && check_set(y, yy)) {
					ans.emplace_back(x.size(), y.size());
				}
			}
			out << ans.size() << std::endl;
			for (const auto& it : ans ) {
				out << it.first << " " << it.second << std::endl;
			}
		}
	}

	bool check_set(const std::multiset<int>& x, const std::set<int>& xx) const {
		const int N = x.size();
		const int M = xx.size();
		return N > 0 && N == M && *xx.begin() == 1 && *xx.rbegin() == N;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
