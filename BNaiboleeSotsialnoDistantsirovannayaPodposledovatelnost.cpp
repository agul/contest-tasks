#include "base/header.hpp"

class BNaiboleeSotsialnoDistantsirovannayaPodposledovatelnost {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		std::vector<int> ans = {a.front()};

		for (int i : range(1, n - 1)) {
			if ((a[i - 1] <= a[i] && a[i] <= a[i + 1]) || (a[i - 1] >= a[i] && a[i] >= a[i + 1])) {
				continue;
			}
			ans.emplace_back(a[i]);
		}

		ans.emplace_back(a.back());

		out << ans.size() << std::endl;
		for (int x : ans) {
			out << x << " ";
		}
		out << std::endl;
	}


	BNaiboleeSotsialnoDistantsirovannayaPodposledovatelnost() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
