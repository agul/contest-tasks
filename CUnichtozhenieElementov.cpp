#include "base/header.hpp"
#include "collections/stack/stack.hpp"

class CUnichtozhenieElementov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		Stack<int> s(n);
		for (int i : range(n - 1)) {
			if (!s.empty() && s.top() < a[i]) {
				continue;
			}
			s.push(a[i]);
		}

		const int mx = *max_element(s.data());
		if (mx > a.back()) {
			out << "NO" << std::endl;
			return;
		}
		out << "YES" << std::endl;
	}


	CUnichtozhenieElementov() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
