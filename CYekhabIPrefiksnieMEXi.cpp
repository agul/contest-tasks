#include "base/header.hpp"

class CYekhabIPrefiksnieMEXi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		std::vector<int> ans(n, -1);
		bool ok = true;

		int cur_mex = 0;
		std::set<int> empty_pos;
		for (int i : range(n)) {
			const int value = a[i];
			if (value == cur_mex) {
				empty_pos.emplace(i);
				continue;
			}
			ans[i] = cur_mex;
			++cur_mex;

			const int count_to_place = value - cur_mex;
			if (empty_pos.size() < count_to_place) {
				ok = false;
				break;
			}

			for (int j : range(count_to_place)) {
				const int pos = *empty_pos.begin();
				empty_pos.erase(pos);

				ans[pos] = cur_mex;
				++cur_mex;
			}
		}
		if (!ok) {
			out << -1 << std::endl;
			return;
		}

		int value = 1000000;
		while (!empty_pos.empty()) {
			const int pos = *empty_pos.begin();
			empty_pos.erase(pos);

			ans[pos] = value;
			--value;
		}

		for (int x : ans) {
			out << x << " ";
		}
		out << std::endl;
	}


	CYekhabIPrefiksnieMEXi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
