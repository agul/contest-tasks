#include "base/header.hpp"

class CDevuIRazbienieMassiva {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, k, p;
		in >> n >> k >> p;
		std::vector<int> a(n);
		in >> a;

		std::vector<int> even;
		std::vector<int> odd;
		for (int i : range(n)) {
			if (a[i] & 1) {
				odd.emplace_back(i);
			} else {
				even.emplace_back(i);
			}
		}

		std::vector<std::vector<int>> ans(k);
		if (odd.size() < k - p || (odd.size() + p - k) % 2 != 0) {
			out << "NO" << std::endl;
			return;
		}
		for (int i : range(k - p)) {
			ans[i].emplace_back(odd.back());
			odd.pop_back();
		}
		for (int i : range(k - p, k)) {
			if (!odd.empty()) {
				ans[i].emplace_back(odd.back());
				odd.pop_back();
				ans[i].emplace_back(odd.back());
				odd.pop_back();
			} else {
				if (even.empty()) {
					out << "NO" << std::endl;
					return;
				}
				ans[i].emplace_back(even.back());
				even.pop_back();
			}
		}
		auto& first_vec = ans.front();
		first_vec.insert(first_vec.end(), all(odd));
		first_vec.insert(first_vec.end(), all(even));
		out << "YES" << std::endl;
		for (const auto& row : ans) {
			out << row.size();
			for (const auto& index : row) {
				out << " " << a[index];
			}
			out << std::endl;
		}
	}


	CDevuIRazbienieMassiva() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
