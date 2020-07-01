#include "base/header.hpp"
#include "collections/stack/stack.hpp"
#include "maths/mod_int.hpp"

class EDvaMassiva {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Int = ModInt<int, 998244353>;

	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		std::vector<int> a(n);
		std::vector<int> b(m);
		in >> a >> b;

		std::vector<int> left_min(n);
		std::iota(all(left_min), 0);

		std::vector<int> right_min(n);
		std::iota(all(right_min), 0);

		Stack<pii> left(n + 1);
		left.push({-1, -1});
		for (int i : range(n)) {
			while (left.top().first >= a[i]) {
				left.pop();
			}
			left_min[i] = left.top().second;
			left.push({a[i], i});
		}


		Stack<pii> right(n + 1);
		right.push({-1, n});
		for (int i : downrange(n)) {
			while (right.top().first > a[i]) {
				right.pop();
			}
			right_min[i] = right.top().second;
			right.push({a[i], i});
		}

		Int ans = 1;
		int index = 0;
		for (int i : range(m)) {
			while (index < n && right_min[index] != n) {
				++index;
			}
			if (index == n) {
				ans *= 0;
				debug(b[i], index);
				break;
			}
			if (i == 0 && a[index] < b[i]) {
				ans *= 0;
				break;
			}
			if (a[index] != b[i]) {
				++index;
				continue;
			}
			if (i > 0) {
				int cur_value = index - left_min[index];
				ans *= cur_value;
			}
			++index;
		}

		out << ans << std::endl;
	}


	EDvaMassiva() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
