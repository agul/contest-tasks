#include "../algolib/cpplib/base/header.hpp"
#include "../algolib/cpplib/bitset.hpp"
#include "../algolib/cpplib/maths/mod_int.hpp"

const int MAXN = 3003;

using bitset = Bitset<MAXN * MAXN>;
using modint = ModInt<int, 998244353>;

bitset begin[32];
bitset end[32];

modint dp[2][MAXN];

class EKaaviIMagicheskoeZaklinanie {
public:
	void solve(std::istream& in, std::ostream& out) {
		// out << "Case #" << ++test_id_ << ": ";
		for (int i : range(32)) {
			begin[i].reset();
			end[i].reset();
		}
		std::string s;
		std::string t;
		in >> s >> t;
		std::vector<int> a(all(s));
		n = a.size();
		std::vector<int> b(all(t));
		m = b.size();
		for (int& x : a) {
			x -= 'a';
		}
		for (int& x : b) {
			x -= 'a';
		}

		for (int i : range(m)) {
			for (int j : range(i, m)) {
				if (i == j) {
					mark(begin[b[i]], i + 1, j + 1);
					mark(end[b[j]], i, i);
					continue;
				} else {
					mark(end[b[j]], i, j);
					mark(begin[b[i]], i + 1, j + 1);
				}
			}
		}

		fill(dp, 0);
		const int cur_char = a.front();
		for (int i : range(m)) {
			if (b[i] == cur_char) {
				dp[0][i] = 2;
			}
		}
		dp[0][m] = 2;

		for (int i : range(m + 1)) {
			if (dp[0][i] > 0) {
				// std::cerr << "dp[" << i << "] = " << dp[0][i] << std::endl;
			}
		}

#ifdef HOME
		int testid = 117;
#else
		int testid = 234;
#endif
		std::cerr << testid << std::endl;

		modint ans = 0;
		if (m == 1) {
			ans += dp[0][0];
		}
		for (int idx : range(1, n)) {
			// std::cerr << s[idx] << " --------- " << ans << std::endl;
			const int next = idx & 1;
			const int prev = next ^ 1;
			const int value = a[idx];
			for (int i : range(m + 1)) {
				dp[next][i] = 0;
			}

			for (int i : range(m + 1)) {
				const modint cur = dp[prev][i];
				const int x = i;
				const int y = std::min(m, i + idx);
				if (cur > 0) {
					if (way_end(x, y, value)) {
						dp[next][x] += cur;
						// std::cerr << "add_end " << x << " " << y << " " << (char)(value + 'a') << std::endl;
					} else
					if (y == m) {
						dp[next][x] += cur;
						// std::cerr << "stp_end " << x << " " << y << " " << (char)(value + 'a') << std::endl;
					}
					if (way_begin(x, y, value)) {
						dp[next][x - 1] += cur;
						// std::cerr << "add_begin " << x << " " << y << " " << (char)(value + 'a') << std::endl;
					}
				}
			}
			if (idx + 1 >= m) {
				ans += dp[next][0];
			}
			dp[next][m] = dp[prev][m] * 2;

			for (int i : range(m + 1)) {
				if (dp[next][i] > 0) {
					// std::cerr << "dp[" << i << "] = " << dp[next][i] << std::endl;
				}
			}
		}
		out << ans << std::endl;

	}

	bool way_begin(const int x, const int y, const int ch) const {
		return begin[ch].get(bit_id(x, y));
	}

	bool way_end(const int x, const int y, const int ch) const {
		return end[ch].get(bit_id(x, y));
	}

	void mark(bitset& set, const int x, const int y) const {
		set.set(bit_id(x, y));
	}

	size_t bit_id(const int x, const int y) const {
		return x * (m + 1) + y;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 1;
	static void generate_test(std::ostream& test) {
		test << std::string(3000, 'a') << std::endl;
		test << std::string(1500, 'a') << std::endl;
	}

private:
	int n, m;
	size_t test_id_ = 0;
};
