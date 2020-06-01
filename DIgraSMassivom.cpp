#include "base/header.hpp"

class DIgraSMassivom {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, s;
		in >> n >> s;
		const int min_value = s / n;
		if (min_value == 1) {
			out << "NO" << std::endl;
			return;
		}
		std::vector<int> a(n, min_value);
		for (int i : range(s % n)) {
			++a[i];
		}
		out << "YES" << std::endl;
		for (int i : a) {
			out << i << " ";
		}
		out << std::endl << 1 << std::endl;
	}


	DIgraSMassivom() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
