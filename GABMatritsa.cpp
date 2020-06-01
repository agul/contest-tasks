#include "base/header.hpp"

class GABMatritsa {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, m, a, b;
		in >> n >> m >> a >> b;
		auto field = make_vector<std::string>(n, std::string(m, '0'));
		int pos = 0;

		for (int i = 0; i < n; ++i) {
			for (int j : range(a)) {
				field[i][pos] = '1';
				pos = (pos + 1) % m;
			}
		}

		for (int j : range(m)) {
			int cnt = 0;
			for (int i : range(n)) {
				cnt += (field[i][j] == '1');
			}
			if (cnt != b) {
				out << "NO" << std::endl;
				return;
			}
		}
		out << "YES" << std::endl;
		for (const auto& row : field) {
			out << row << std::endl;
		}

	}


	GABMatritsa() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
