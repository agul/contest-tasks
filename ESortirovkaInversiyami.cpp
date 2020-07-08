#include "base/header.hpp"

class ESortirovkaInversiyami {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		std::vector<pii> inversions;
		std::vector<pii> ans;

		for (int i : range(n)) {
			for (int j : range(i + 1, n)) {
				if (a[i] > a[j]) {
					inversions.emplace_back(i, j);
				}
			}
		}

		for (int i : range(n)) {
			std::vector<pii> vals;
			for (int j : range(i + 1, n)) {
				if (a[i] > a[j]) {
					vals.emplace_back(a[j], j);
				}
			}
			sort(vals, std::greater<>());
			for (const auto& it : vals) {
				ans.emplace_back(i, it.second);
			}
		}


		auto tmp = ans;
		sort(tmp);
		assert(tmp == inversions);
#ifdef HOME
		out << ans.size() << std::endl;
		for (const auto& it : ans) {
			out << it.first + 1 << " " << it.second + 1 << std::endl;
		}
#else
		printf("%d\n", ans.size());
		for (const auto& it : ans) {
			printf("%d %d\n", it.first + 1, it.second + 1);
		}
#endif
	}


	ESortirovkaInversiyami() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int testsCount = 1;
		for (int testid : range(testsCount)) {
			int n;
			in >> n;
			std::vector<int> a(n);
			in >> a;

			int k;
			out >> k;
			for (int i : range(k)) {
				int x, y;
				out >> x >> y;
				--x, --y;
				std::swap(a[x], a[y]);
			}

			auto b = a;
			sort(a);
			if (a != b) {
				debug(testid, a, b);
				return false;
			}

		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 100;
		const int kMaxm = 1000000;

		const int n = Random::get(1, kMaxn);
		test << n << std::endl;
		for (int i : range(n)) {
			test << Random::get(0, kMaxm) << " ";
		}
		test << std::endl;
	}

};
