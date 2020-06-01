#include "base/header.hpp"

class BMaryaIvanovnaNarushaetSamoizolyatsiyu {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;
		sort(a);

		int ans = 1;
		int index = 0;
		while (index < a.size()) {
			int start = a[index];
			while (index < a.size() && a[index] == start) {
				++index;
			}
			if (index + 1 > start) {
				umax(ans, index + 1);
			}
		}
		out << ans << std::endl;
	}


	BMaryaIvanovnaNarushaetSamoizolyatsiyu() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int pans;
		out >> pans;

		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		sort(a);
		int cnt = 1;
		int md = a[0];
		for (int x : a) {

		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 100;
		const int kMaxm = 100;

		const int n = Random::get(1, kMaxn);
		test << 1 << std::endl;
		test << n << std::endl;
		for (int i = 0; i < n; ++i) {
			test << Random::get(1, kMaxm) << " ";
		}
		test << std::endl;
	}

};
