#include "base/header.hpp"
#include "maths/mod_int.hpp"

class BDzhonniIGrossmeister {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	using Int = ModInt<int, 1000000007>;

	static constexpr int kMaxn = 1111111;

	using Map = std::map<int, int>;

	void solve(std::istream& in, std::ostream& out) {
		int n, p;
		Map cnt;
		input(in, n, p, cnt);

		if (p == 1) {
			out << n % 2 << std::endl;
			return;
		}

		Int sum_a = 0;
		Int sum_b = 0;
		const Int pp = p;

		while (!cnt.empty()) {
			auto it = cnt.rbegin();
			it->second %= 2;

			int deg, count;
			std::tie(deg, count) = *it;

			if (count == 0) {
				cnt.erase(deg);
				continue;
			}

			bool matched = false;

			/* const int kMaxPow = 24;
			std::vector<int> cur_cnt(kMaxPow, 0);
			for (int i : range(kMaxPow)) {
				const auto it = cnt.find(deg - i);
				cur_cnt[i] = (it == cnt.cend() ? 0 : it->second);
			}

			for (int i : range(1, kMaxPow)) {
				while (!matched && cur_cnt[i] >= p) {
					int cur_pos = i;
					while (cur_cnt[cur_pos] >= p) {
						cur_cnt[cur_pos] -= p;
						cur_cnt[cur_pos - 1] += 1;
						if (cur_pos - 1 == 0) {
							matched = true;
							break;
						}
						if (cur_cnt[cur_pos - 1] >= p) {
							--cur_pos;
						}
					}
				}
			}

			for (int i : range(1, kMaxPow)) {
				if (cur_cnt[i] == 0) {
					cnt.erase(deg - i);
				} else {
					cnt[deg - i] = cur_cnt[i];
				}
			} */

			auto iter = std::next(it);
			while (!matched && iter != cnt.rend()) {
				const int index = iter->first;
				// debug(index, iter->second);
				if (iter->second < p) {
					++iter;
					continue;
				}
				// debug("PASSED", index);

				bool force_stop = false;
				while (iter->second >= p) {
					// debug("INNER", iter->first);
					iter->second -= p;
					const int cur_index = iter->first;
					auto next = cnt.find(cur_index + 1);
					if (next == cnt.cend()) {
						// debug("NOT FOUND", cur_index + 1);
						cnt[cur_index + 1] = 1;
						force_stop = true;
						break;
					}
					next->second += 1;
					// debug("FOUND", cnt);
					if (next->first == deg) {
						matched = true;
						break;
					}
					if (next->second >= p) {
						iter = std::make_reverse_iterator(std::next(next));
						// debug("ITER GO", iter->first);
					}
				}
				if (force_stop) {
					iter = std::make_reverse_iterator(std::next(cnt.find(index)));
					// debug("FORCE STOP", index, cnt);
				} else {
					++iter;
				}
			}
			cnt.erase(deg);
			if (matched) {
				continue;
			}
			if (!matched) {
				sum_a += binpow(pp, deg);
				for (const auto& it : cnt) {
					if (it.second > 0) {
						sum_b += binpow(pp, it.first) * it.second;
					}
				}
				break;
			}
		}

		out << (sum_a - sum_b) << std::endl;
	}

	void input(std::istream& in, int& n, int& p, Map& cnt) {
#define FAST_INPUT 0
#if !FAST_INPUT
		in >> n >> p;
		for (int i : range(n)) {
			int x;
			in >> x;
			++cnt[x];
		}
#else
		scanf("%d%d", &n, &p);
		for (int i : range(n)) {
			int x;
			scanf("%d", &x);
			++cnt[x];
		}
#endif
	}

	BDzhonniIGrossmeister() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int pans;
		out >> pans;

		const int jans = 0;

		return pans == jans;
	}


	static constexpr size_t kGeneratedTestsCount = 4;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {
		static int test_id = 0;
		++test_id;

		int cur_id = 0;
		if (test_id == ++cur_id) {
			const int n = 1000000;
			test << 1 << std::endl;
			test << n << " " << 2 << std::endl;
			for (int i : inclusiveDownrange(n - 2)) {
				test << i << " ";
			}
			test << 0 << std::endl;
			return;
		}

		if (test_id == ++cur_id) {
			const int n = 1 << 19;
			test << 1 << std::endl;
			test << n + 1 << " " << 2 << std::endl;
			for (int i : range(n)) {
				test << "0 ";
			}
			test << 19 << std::endl;
			return;
		}

		if (test_id == ++cur_id) {
			const int n = 1 << 20;
			test << 1 << std::endl;
			test << n << " " << 2 << std::endl;
			for (int i : range(n)) {
				test << (1 << 20) << " ";
			}
			test << std::endl;
			return;
		}

		if (test_id == ++cur_id) {
			const int n = 1 << 20;
			test << 1 << std::endl;
			test << n << " " << 2 << std::endl;
			for (int i : range(n - 3)) {
				test << (1 << 20) << " ";
			}
			test << ((1 << 20) - 1) << " " << ((1 << 20) - 2) << " " << ((1 << 20) - 2) << std::endl;
			return;
		}
	}

};
