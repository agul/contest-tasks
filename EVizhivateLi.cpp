#include "base/header.hpp"

class EVizhivateLi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n, m;
		in >> n >> m;
		std::vector<int> a(n);
		in >> a;

		std::vector<pii> friends;
		friends.reserve(m);

		std::vector<std::set<int>> people(n);
		for (int i : range(m)) {
			int x, y;
			in >> x >> y;
			--x, --y;
			people[x].emplace(i);
			people[y].emplace(i);
			friends.emplace_back(x, y);
		}

		std::map<int, std::set<int>> food;

		auto add_food = [&food, &a](const int item) {
			food[a[item]].emplace(item);
		};

		auto decrease = [&food, &a, &add_food](const int item, const int delta = 1) {
			if (a[item] < delta) {
				return false;
			}
			auto it = food.find(a[item]);
			it->second.erase(item);
			if (it->second.empty()) {
				food.erase(it);
			}

			a[item] -= delta;
			add_food(item);
			return true;
		};

		for (int i : range(n)) {
			add_food(i);
		}

		auto fail = [&out]() {
			out << "DEAD" << std::endl;
		};

		bool ok = true;
		std::vector<bool> eaten(m, false);
		std::vector<int> order;
		order.reserve(m);
		int cnt_friends = m;
		while (!food.empty() && cnt_friends > 0) {
			auto it = food.begin();
			auto& cur_set = it->second;
			const int plates = it->first;

			debug("##################");
			debug(plates, cur_set, a);

			while (!cur_set.empty()) {
				debug(cur_set);
				auto food_item_iter = cur_set.begin();
				const int item = *food_item_iter;
				debug(item);

				bool any = false;
				auto& people_set = people[item];
				while (!people_set.empty()) {
					auto iter = people_set.begin();
					const int person = *iter;
					debug(person);
					people_set.erase(iter);
					if (eaten[person]) {
						continue;
					}

					order.emplace_back(person);

					int x, y;
					std::tie(x, y) = friends[person];
					if (a[x] == 0 && a[y] == 0) {
						debug("FAIL", person, a);
						fail();
						return;
					}

					debug("eat", person);
					decrease(x);
					decrease(y);

					eaten[person] = true;
					--cnt_friends;
					any = true;
					break;
				}
				if (people_set.empty()) {
					cur_set.erase(item);
				}
				if (any) {
					break;
				}
			}
			if (cur_set.empty()) {
				food.erase(plates);
			}
		}
		debug(order);

		if (ok && order.size() == m) {
			out << "ALIVE" << std::endl;
			for (int x : order) {
				out << x + 1 << " ";
			}
			out << std::endl;
			return;
		}
		fail();
	}


	EVizhivateLi() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		std::string jans;
		jury >> jans;

		std::string pans;
		out >> pans;

		if (pans != jans) {
			debug(jans, pans);
			return false;
		}

		if (pans == "DEAD") {
			return true;
		}

		int n, m;
		in >> n >> m;
		std::vector<int> a(n);
		std::vector<pii> friends(m);
		in >> a >> friends;

		std::vector<int> order(m);
		out >> order;

		for (int v : order) {
			int x, y;
			std::tie(x, y) = friends[v - 1];
			--x, --y;

			if (a[x] == 0 && a[y] == 0) {
				debug("FAIL", v, x, y);
				return false;
			}

			a[x] = std::max(0, a[x] - 1);
			a[y] = std::max(0, a[y] - 1);
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
