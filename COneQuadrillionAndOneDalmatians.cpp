#include "base/header.hpp"

class COneQuadrillionAndOneDalmatians {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		ll n;
		in >> n;
		
		std::string ans;
		while (n > 0) {
			--n;
			ans += (n % 26) + 'a';
			n /= 26;
		}
		reverse(ans);
		out << ans << std::endl;
	}


	COneQuadrillionAndOneDalmatians() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
