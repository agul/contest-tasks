#include "base/header.hpp"
#include "base/functors/min.hpp"
#include "segment_tree/top_down_segment_tree.hpp"

struct ApplyUpdate : Applier<int> {
	int operator()(const int& value, const int& update, const size_t left, const size_t right) const {
		return value + update;
	}
};

struct MergeUpdates : Merger<int> {
	int operator()(const int& acc_updates, const int& update) const {
		return acc_updates + update;
	}
};

using SegmentTree = TopDownSegmentTree<int, Min, int, ApplyUpdate, MergeUpdates>;

class rucode_b {
public:
	std::string solve_fast(std::vector<int> a) const {
		const int n = a.size() / 2;
		auto pos = make_vector<int>(n, 0, -1);
		for (int i : range(n * 2)) {
			int& x = a[i];
			--x;
			pos[x].emplace_back(i);
		}

		if (n % 2 == 1) {
			return "(";
		}

		std::vector<int> ans(n * 2, 0);

		int open_brackets_cnt = 0;
		int L = 0;
		int R = ans.size() - 1;
		int left_balance = 0;
		int right_balance = 0;

		auto ans_to_str = [](const std::vector<int>& ans) {
			std::string res;
			for (int x : ans) {
				if (x == 0) {
					res += 'X';
					continue;
				}
				res += (x == 1 ? '(' : ')');
			}
			return res;
		};

		std::vector<int> init_open(n * 2);
		std::vector<int> init_close(n * 2);
		for (int i : range(n * 2)) {
			init_open[i] = (n * 2 - i) / 2;
			init_close[i] = (i + 1) / 2;
		}

		SegmentTree min_open(n * 2, INF);
		SegmentTree min_close(n * 2, INF);

		min_open.build(init_open.data());
		min_close.build(init_close.data());

		auto reached_open_limit = [&min_open](const int from, const int to) {
			return min_open.get(from, to) == 0;
		};

		auto reached_close_limit = [&min_close](const int from, const int to) {
			return min_close.get(from, to) == 0;
		};

		auto set_bracket = [&pos, &ans, &open_brackets_cnt, &min_open, &min_close](const int value, const int bracket) {
			const int N = ans.size();
			for (int x : pos[value]) {
				ans[x] = bracket;
				if (bracket == 1) {
					min_open.range_update(0, x, -1);
				} else {
					min_close.range_update(x, N - 1, -1);
				}
			}
			if (bracket == 1) {
				open_brackets_cnt += 2;
			}
		};

		while (L <= R) {
			if (left_balance < 0 || right_balance > 0) {
				return "(";
			}

			if (L <= R && ans[L] != 0) {
				left_balance += ans[L];
				++L;
			}
			else if (L <= R && ans[R] != 0) {
				right_balance += ans[R];
				--R;
				continue;
			}
			else if (reached_close_limit(L, n * 2 - 1)) {
				set_bracket(a[L], 1);
			}
			else if (reached_open_limit(0, R)) {
				set_bracket(a[R], -1);
			}
			else if (open_brackets_cnt < n) {
				set_bracket(a[L], 1);
			}
			else if (open_brackets_cnt >= n) {
				set_bracket(a[L], -1);
			} else {
				assert(false);
			}
		}

		if (left_balance + right_balance != 0) {
			return "(";
		}
		return ans_to_str(ans);
	}

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		auto a = make_vector<int>(n * 2, 0);
		in >> a;

		const std::string ans = solve_fast(a);
		out << ans << std::endl;
	}

	std::string solve_slow(std::vector<int> a) const {
		const int n = a.size() / 2;
		for (int& x : a) {
			--x;
		}
		std::string ans;
		for (int mask : range(1 << n)) {
			if (popcount(mask) != n / 2) {
				continue;
			}
			int balance = 0;
			bool ok = true;
			std::string cur_str;
			for (int x : a) {
				if (mask & (1 << x)) {
					if (balance == 0) {
						ok = false;
						break;
					}
					--balance;
					cur_str += ')';
				} else {
					++balance;
					cur_str += '(';
				}
			}
			ok &= (balance == 0);
			if (ok && (ans.empty() || cur_str < ans)) {
				ans = cur_str;
			}
		}
		if (ans.empty()) {
			return "(";
		}
		return ans;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		std::istringstream in(input);
		std::istringstream out(actual_output);

		int n;
		in >> n;
		auto a = make_vector<int>(n * 2, 0);
		in >> a;
		const std::string jans = solve_slow(a);

		std::string pans;
		out >> pans;
		if (jans != pans) {
			// debug(input);
			// debug(jans, pans);
		}
		return jans == pans;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {
		const int n = rand() % 18 + 4;
		test << n << std::endl;
		std::vector<int> a(n * 2);
		for (int i : range(n)) {
			a[i] = i;
			a[i + n] = i;
		}
		std::random_shuffle(all(a));
		for (int x : a) {
			test << x + 1 << " ";
		}
		test << std::endl;
	}

private:
	size_t test_id_ = 0;
};
