#include "base/header.hpp"

class DOchistkaTelefona {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        ll m;
        in >> n >> m;
        std::vector<ll> sizes(n);
        in >> sizes;

        std::vector<ll> trash;
        std::vector<ll> important;

        for (int i : range(n)) {
            int weight;
            in >> weight;
            if (weight == 1) {
                trash.emplace_back(sizes[i]);
            } else {
                important.emplace_back(sizes[i]);
            }
        }

        sort(trash);
        sort(important);

        auto get_trash_size = [&trash] {
            if (trash.size() == 1) {
                return trash.back();
            }
            return trash.back() + trash[trash.size() - 2];
        };

        ll ans = 0;
        auto take = [&ans, &m](std::vector<ll>& sizes, const ll delta) {
            m -= sizes.back();
            sizes.pop_back();
            ans += delta;
        };

        while (m > 0 && (!trash.empty() || !important.empty())) {
            if (important.empty()) {
                take(trash, 1);
                continue;
            }

            if (trash.empty()) {
                take(important, 2);
                continue;
            }

            const ll trash_size = get_trash_size();

            if (trash_size >= m || trash_size >= important.back()) {
                take(trash, 1);
            } else {
                take(important, 2);
            }
        }

        if (m > 0) {
            ans = -1;
        }
        out << ans << std::endl;
	}


	DOchistkaTelefona() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
