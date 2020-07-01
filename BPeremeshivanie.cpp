#include "base/header.hpp"

class BPeremeshivanie {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, x, m;
		in >> n >> x >> m;
		int L = x;
		int R = x;
		for (int i : range(m)) {
			int from, to;
			in >> from >> to;
			if (from <= R && to >= L) {
				umax(R, to);
				umin(L, from);
			}
		}
		out << R - L + 1 << std::endl;
	}


	BPeremeshivanie() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
