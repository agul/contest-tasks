#include "base/header.hpp"

class FStrokaShpion {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	bool validate(const std::vector<std::string>& a, const std::string& s) {
		for (const auto& str : a) {
			int cnt = 0;
			for (int i : range(s.length())) {
				if (s[i] != str[i]) {
					++cnt;
					if (cnt > 1) {
						return false;
					}
				}
			}
		}
		return true;
	}

	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		std::vector<std::string> a(n);
		in >> a;

		std::string s = a.front();
		if (validate(a, s)) {
			out << s << std::endl;
			return;
		}

		for (int pos : range(m)) {
			for (char ch : inclusiveRange('a', 'z')) {
				s[pos] = ch;

				if (validate(a, s)) {
					out << s << std::endl;
					return;
				}

			}
			s = a.front();
		}

		out << -1 << std::endl;

	}


	FStrokaShpion() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
