#include "base/header.hpp"

class ERedScarf {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		int sum_xor = 0;
		std::vector<int> a(n);
		in >> a;

		for (int x : a) {
			sum_xor ^= x;
		}

		for (int x : a) {
			out << (sum_xor ^ x) << " ";
		}
		out << std::endl;
	}


	ERedScarf() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
