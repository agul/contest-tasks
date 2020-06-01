#include "base/header.hpp"

class EKPeriodichnayaGirlyanda {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		std::string s;
		in >> n >> k >> s;
		std::vector<int> a(all(s));
		for (int& x : a) {
			x -= '0';
		}

		const int count_ones = std::count(all(a), 1);
		int ans = count_ones;
		for (int rem : range(k)) {
			int cur_ones_cnt = 0;
			int first_one = -1;
			for (int i = rem; i < n; i += k) {
				if (a[i] == 1) {
					if (cur_ones_cnt == 0) {
						first_one = i;
					}
					++cur_ones_cnt;
				}
			}
			if (cur_ones_cnt == 0) {
				continue;
			}
			int last = 0;
			int cnt = 0;
			int prev = 0;
			std::vector<pii> values = {{1, 1}};
			for (int i = first_one + k; i < n; i += k) {
				if (a[i] == values.back().X) {
					++values.back().Y;
				} else {
					values.emplace_back(a[i], 1);
				}
			}
			if (values.back().X == 0) {
				values.pop_back();
			}

			std::vector<int> pref;
			int pref_sum = cur_ones_cnt;
			for (int i = 0; i < values.size(); ++i) {
				if (values[i].X == 1) {
					pref_sum -= values[i].Y;
					pref.emplace_back(pref_sum);
				} else {
					pref_sum += values[i].Y;
				}
			}
			debug(pref);
			int min_value = 0;
			int value = 0;
			int index = 0;
			for (int x : pref) {
				debug(x, min_value);
				umin(ans, count_ones - cur_ones_cnt + x + min_value);

				value += values[index].Y;
				++index;
				value -= values[index].Y;
				++index;

				umin(min_value, value);
			}
		}
		out << ans << std::endl;
	}


	EKPeriodichnayaGirlyanda() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};
