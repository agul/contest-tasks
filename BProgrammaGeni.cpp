#include "base/header.hpp"

class BProgrammaGeni {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<std::string> a(n);
		in >> a;

		int cnt = 0;
		int non_beauty = -1;
		bool zero = false;
		for (int i : range(n)) {
			int len = a[i].size();
			zero |= (a[i] == "0");
			if ("1" + std::string(len - 1, '0') != a[i]) {
				non_beauty = i;
			} else {
				cnt += len - 1;
			}
		}
		if (non_beauty == -1) {
			non_beauty = 0;
			cnt -= a.front().size() - 1;
		}

		if (zero) {
			out << 0 << std::endl;
			return;
		}
		out << a[non_beauty] << std::string(cnt, '0') << std::endl;

	}


	BProgrammaGeni() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};
