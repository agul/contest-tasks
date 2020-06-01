#include "base/header.hpp"

class BOrakIMediani {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		std::vector<int> a(n);
		in >> a;

		bool any_zero = false;
		for (int& x : a) {
			if (x == k) {
				x = 0;
				any_zero = true;
			}
			else if (x < k) {
				x = -1;
			}
			else {
				x = 1;
			}
		}

		if (n == 1) {
			out << (any_zero ? "yes" : "no") << std::endl;
			return;
		}
		if (!any_zero) {
			out << "no" << std::endl;
			return;
		}

		int prev_ge_k = -INF;
		for (int i : range(n)) {
			if (a[i] >= 0) {
				if (i - prev_ge_k <= 2) {
					out << "yes" << std::endl;
					return;
				}
				prev_ge_k = i;
			}
		}
		out << "no" << std::endl;
		return;

		SafeUnorderedMap<int, int> prefs;
		prefs[0] = -1;

		auto check = [&prefs](const int sum, const int pos, const int prev_k) {
			const auto it = prefs.find(sum);
			return it != prefs.cend() && it->second <= prev_k && it->second + 1 < pos;
		};

		int sum = 0;
		int prev_k = -INF;
		bool ok = false;
		for (int i : range(n)) {
			sum += a[i];
			if (a[i] == 0) {
				ok |= (i - prev_k <= 2);
				prev_k = i;
			}
			ok |= (check(sum, i, prev_k) || check(sum - 1, i, prev_k));
			if (prefs.count(sum) == 0) {
				prefs[sum] = i;
			}
		}
		out << (ok ? "yes" : "no") << std::endl;

	}


	BOrakIMediani() {}

	bool solve_slow(const std::vector<int>& a, int k) {
		const int n = a.size();
		if (n == 1) {
			return a.front() == k;
		}
		for (int i : range(n)) {
			int eq = 0;
			int less = 0;
			int greater = 0;
			int cnt = 0;
			for (int j : range(i, n)) {
				if (a[j] > k) {
					greater++;
				}
				else if (a[j] < k) {
					less++;
				} else {
					eq++;
				}
				++cnt;
				const int med = (cnt + 1) / 2;
				if (cnt > 1 && eq > 0 && less < med && less + eq >= med) {
					return true;
				}
			}
		}
		return false;
	}

	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int t;
		in >> t;
		for (int i : range(t)) {
			int n, k;
			in >> n >> k;
			std::vector<int> a(n);
			in >> a;

			std::string p_token;
			out >> p_token;
			const bool pans = (p_token == "yes");
			const bool jans = solve_slow(a, k);
			if (pans != jans) {
				debug(i, pans, jans);
				return false;
			}
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1000;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 100;
		const int kMaxValue = 500000;

		const int n = Random::get(1, kMaxn);
		std::vector<int> a(n);
		for (int& x : a) {
			x = Random::get(1, kMaxValue);
		}
		// const int k = a[Random::get(0, kMaxn - 1)];
		const int k = Random::get(1, kMaxValue);

		test << 1 << std::endl;
		test << n << " " << k << std::endl;
		for (int x : a) {
			test << x << " ";
		}
		test << std::endl;
	}

};
