#include "base/header.hpp"

class ENoviiGodITriMushketyora {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, a, b, c;
		in >> n >> a >> b >> c;
		std::vector<int> p(n);
		in >> p;
		sort(p);
		reverse(p);

		const std::vector<int> tmp = sorted(std::vector<int>{a, b, c});
		std::tie(a, b, c) = std::tie(tmp[0], tmp[1], tmp[2]);

		if (p.front() > a + b + c) {
			out << -1 << std::endl;
			return;
		}

		std::multiset<int> opponents(all(p));

		auto get_opponent = [&opponents](const int max_force) {
			if (opponents.empty()) {
				return -1;
			}
			auto it = opponents.upper_bound(max_force);
			if (it == opponents.cbegin()) {
				return -1;
			}
			it = std::prev(it);
			const int cur_opponent = *it;
			opponents.erase(it);
			return cur_opponent;
		};

		auto get_strongest_opponent = [&opponents, a, b, c, &get_opponent]() {
			return get_opponent(a + b + c);
			if (opponents.empty()) {
				return -1;
			}
			auto it = std::prev(opponents.cend());
			const int cur_opponent = *it;
			opponents.erase(it);
			return cur_opponent;
		};

		int ans = 0;
		while (!opponents.empty()) {
			++ans;
			const int cur_opponent = get_strongest_opponent();
			if (cur_opponent > b + c) {
				// kill together
				continue;
			}

			if (cur_opponent <= a) {
				get_opponent(b);
				get_opponent(c);
				continue;
			}

			if (cur_opponent <= b) {
				get_opponent(c);
				get_opponent(a);
				continue;
			}

			if (cur_opponent <= c) {
				const int x = get_opponent(a);
				const int y = get_opponent(b);
				if (x == -1 && y == -1) {
					get_opponent(a + b);
				}
				continue;
			}

			if (cur_opponent <= a + b) {
				get_opponent(c);
				continue;
			}

			if (cur_opponent <= a + c) {
				get_opponent(b);
				continue;
			}

			if (cur_opponent <= b + c) {
				get_opponent(a);
				continue;
			}
		}

		out << ans << std::endl;
	}


	ENoviiGodITriMushketyora() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
