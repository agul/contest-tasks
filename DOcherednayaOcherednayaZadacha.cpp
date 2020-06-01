#include "base/header.hpp"
#include "data_structures/sparse_table.hpp"

class DOcherednayaOcherednayaZadacha {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		std::vector<int> prefs = {0};
		for (int x : a) {
			prefs.emplace_back(prefs.back() + x);
		}

		SparseTableCmp<int, std::greater<>> max_sum_table(prefs);
		SparseTableCmp<int, std::less<>> min_sum_table(prefs);

		SparseTableCmp<int, std::greater<>> max_table(a);

		auto binary_search = [&max_table, &a](const int index, const int left, const int right) {
			int L = left;
			int R = right;
			const bool left_search = (right == index);
			const int cur_value = a[index];
			while (R - L > 1) {
				const int md = (L + R) / 2;
				const int left_index = std::min(index, md);
				const int right_index = std::max(index, md);
				const int max_index = max_table.query(left_index, right_index + 1);
				const int max_value = a[max_index];
				if (max_value > cur_value) {
					(left_search ? L : R) = md;
				} else {
					(left_search ? R : L) = md;
				}
			}
			return (left_search ? R : L);
		};

		int ans = 0;
		for (int i : inclusiveRange(1, n)) {
			const int left_index = binary_search(i - 1, -1, i - 1);
			const int right_index = binary_search(i - 1, i - 1, n);
			// debug(i, left_index, right_index);

			const int max_index = max_sum_table.query(i, right_index + 2);
			const int min_index = min_sum_table.query(left_index, i);

			const int max = prefs[max_index];
			const int min = prefs[min_index];

			const int cur_sum = max - min;
			umax(ans, cur_sum - a[i - 1]);

			// debug(i, ans, min, max, min_index, max_index);
		}
		out << ans << std::endl;

	/*
		std::map<int, std::vector<int>> sums;
		for (int i : inclusiveDownrange(n, 1)) {
			sums[prefs[i]].emplace_back(i);
		}
		int ans = 0;
		for (int i : range(n)) {
			const int pref_sum = prefs[i + 1];
			auto it = sums.rbegin();

			const int best_pref_sum = it->first;
			const int right = it->second.back();

			umax(ans, best_pref_sum - prefs[i] - a[max_table.query(i, right)]);
			debug(i, ans, best_pref_sum, right);
			sums[pref_sum].pop_back();
			if (sums[pref_sum].empty()) {
				sums.erase(pref_sum);
			}
		}
		out << ans << std::endl;
	 */
	}


	DOcherednayaOcherednayaZadacha() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;

		int jans = 0;
		for (int i : range(n)) {
			int sum = a[i];
			int mx = a[i];
			for (int j : range(i + 1, n)) {
				sum += a[j];
				umax(mx, a[j]);
				umax(jans, sum - mx);
			}
		}

		int pans;
		out >> pans;
		if (jans != pans) {
			debug(pans, jans);
			return false;
		}

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 10;
		const int kMaxm = 30;
#ifdef USE_JNGEN
		const int n = Random::get(1, kMaxn);
		auto a = jngen::Array::random(n, -kMaxm, kMaxm);
		test << a.size() << std::endl << a << std::endl;
#endif
	}

};
