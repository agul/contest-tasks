#include "base/header.hpp"

class BDvaMassivaIObmeni {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		std::vector<int> a(n);
		std::vector<int> b(n);
		in >> a >> b;
		sort(a);
		sort(b);
		reverse(b);
		ll ans = 0;
		for (int i : range(k)) {
			ans += std::max(a[i], b[i]);
		}
		for (int i : range(k, n)) {
			ans += a[i];
		}
		out << ans << std::endl;
	}


	BDvaMassivaIObmeni() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};
