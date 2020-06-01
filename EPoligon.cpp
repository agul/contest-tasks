#include "base/header.hpp"

class EPoligon {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<std::string> a(n);
		in >> a;

		bool ok = true;
		for (int i : range(n)) {
			for (int j : range(n)) {
				if (a[i][j] == '1') {
					ok &= (i == n - 1 || j == n - 1 || (a[i + 1][j] == '1' || a[i][j + 1] == '1'));
				}
			}
		}
		out << (ok ? "YES" : "NO") << std::endl;
	}


	EPoligon() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
