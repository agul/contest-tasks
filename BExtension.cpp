#include "base/header.hpp"
#include "maths/mod_int.hpp"

class BExtension {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Field = std::vector<std::vector<bool>>;

	std::set<Field> fields;

	void dfs(Field& field, int a, int b, int x, int y) {
		if (a == x && b == y) {
			fields.emplace(field);
			return;
		}
		if (a < x) {
			for (int j : range(b)) {
				field[a][j] = true;
				dfs(field, a + 1, b, x, y);
				field[a][j] = false;
			}
		}
		if (b < y) {
			for (int i : range(a)) {
				field[i][b] = true;
				dfs(field, a, b + 1, x, y);
				field[i][b] = false;
			}
		}
	}

	using Int = ModInt<int, 998244353>;

	void solve(std::istream& in, std::ostream& out) {
		int a, b, c, d;
		in >> a >> b >> c >> d;

//		for (int x : inclusiveRange(a, c)) {
//			for (int y : inclusiveRange(b, d)) {
//				fields.clear();
//				auto field = make_vector<bool>(x, y, false);
//				dfs(field, a, b, x, y);
//				debug(x, y, fields.size());
//			}
//		}

		auto dp = make_vector<Int>(c + 1, d + 1, 0);
//		for (int i : inclusiveRange(a)) {
//			for (int j : inclusiveRange(b)) {
//				dp[i][j] = 1;
//			}
//		}

		dp[a][b] = 1;

		for (int i : inclusiveRange(a, c)) {
			for (int j : inclusiveRange(b, d)) {
				if (i == a && j == b) {
					continue;
				}
				dp[i][j] = dp[i - 1][j] * j + dp[i][j - 1] * i - dp[i - 1][j - 1] * (i - 1) * (j - 1);
			}
		}

		debug(dp);

		out << dp[c][d] << std::endl;
	}


	BExtension() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
