#include "base/header.hpp"

class DPostroenieMassiva {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		auto cmp = [](const pii& lhs, const pii& rhs) {
			const int left_size = lhs.Y - lhs.X;
			const int right_size = rhs.Y - rhs.X;
			return left_size < right_size || (left_size == right_size && lhs > rhs);
		};
		std::priority_queue<pii, std::vector<pii>, decltype(cmp)> q(cmp);
		q.push({0, n - 1});
		std::vector<int> ans(n, -1);
		int iter = 1;
		while (!q.empty()) {
			const auto it = q.top();
			q.pop();
			int x;
			int y;
			std::tie(x, y) = it;
			if (y < x) {
				continue;
			}

			if ((y - x) % 2 == 1) {
				const int md = (x + y - 1) / 2;
				ans[md] = iter++;
				q.push({md + 1, y});
				q.push({x, md - 1});
			} else {
				const int md = (x + y) /  2;
				ans[md] = iter++;
				q.push({x, md - 1});
				q.push({md + 1, y});
			}
		}
		for (int x : ans) {
			out << x << " ";
		}
		out << std::endl;
	}


	DPostroenieMassiva() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};
