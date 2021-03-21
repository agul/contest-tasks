#include "base/header.hpp"

class BSkidki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;
        std::vector<pli> chairs, pencils;
        std::vector<ll> items;
        for (int i : range(n)) {
            ll price;
            int type;
            in >> price >> type;
            price *= 2;
            (type == 1 ? chairs : pencils).emplace_back(price, i);
            items.emplace_back(price);
        }
        sort(chairs);
        sort(pencils);

        const int baskets_with_chairs = std::min<int>(k, chairs.size());

        auto res = make_vector<int>(k, 0, 0);
        if (baskets_with_chairs < k) {
            reverse(pencils);
            for (int i : range(k - baskets_with_chairs)) {
                res[k - 1 - i].emplace_back(pencils.back().second);
                pencils.pop_back();
            }
            reverse(pencils);
        }

        for (int i : range(baskets_with_chairs)) {
            res[i].emplace_back(chairs.back().second);
            chairs.pop_back();
        }
        std::transform(all(chairs), std::back_inserter(res.back()), [](const pli& chair) {
            return chair.second;
        });

        for (int i : range(k)) {
            const int chair_id = res[i].back();
            const ll chair_price = items[chair_id];

            while (!pencils.empty() && pencils.back().first > chair_price) {
                res[i].emplace_back(pencils.back().second);
                pencils.pop_back();
            }
        }
        std::transform(all(pencils), std::back_inserter(res.back()), [](const pli& pencil) {
            return pencil.second;
        });

        ll ans = 0;
        int basket_id = 0;
        for (const auto& basket : res) {
            ll min_price = LINF;
            for (const auto& item : basket) {
                ans += items[item];
                umin(min_price, items[item]);
            }
            if (basket_id < baskets_with_chairs) {
                ans -= min_price / 2;
            }
            ++basket_id;
        }
        out << ans / 2 << "." << ans % 2 * 5 << std::endl;
        for (const auto& basket : res) {
            out << basket.size();
            for (const auto& item : basket) {
                out << " " << item + 1;
            }
            out << std::endl;
        }
	}


	BSkidki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
