#include "base/header.hpp"

class CPriyateLi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		std::vector<int> a(n);
		std::vector<int> w(k);
		in >> a >> w;
		sort(a);
		sort(w, std::greater<>());

		auto friends = make_vector<int>(k, 0, 0);
		for (int i : downrange(k)) {
			friends[i].emplace_back(a.back());
			a.pop_back();
		}
		reverse(a);

		for (int i : range(k)) {
			for (int j : range(w[i] - 1)) {
				friends[i].emplace_back(a.back());
				a.pop_back();
			}
		}
		ll ans = 0;
		for (int i : range(k)) {
			ans += friends[i].front();
			const int index = std::min<int>(1, friends[i].size() - 1);
			ans += friends[i][index];
		}
		out << ans << std::endl;
	}


	CPriyateLi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
