#include "base/header.hpp"
#include "collections/stack/stack.hpp"

class B01Igra {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		in >> s;

		Stack<char> stack(s.length());
		int cnt = 0;
		for (char ch : s) {
			if (!stack.empty() && stack.top() != ch) {
				stack.pop();
				++cnt;
				continue;
			}
			stack.push(ch);
		}
		if (cnt % 2 == 1) {
			out << "DA" << std::endl;
			return;
		}
		out << "NET" << std::endl;
	}


	B01Igra() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
