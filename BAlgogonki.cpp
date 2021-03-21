#include "base/header.hpp"

class BAlgogonki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	const int kMaxChanges = 100;

	void solve(std::istream& in, std::ostream& out) {
        int n, m, r;
        in >> n >> m >> r;
        auto cars = make_vector<ll>(m, n, n, 0);
        in >> cars;

        for (auto& car : cars) {
            for (int k : range(n)) {
                for (int i : range(n)) {
                    for (int j : range(n)) {
                        umin(car[i][j], car[i][k] + car[k][j]);
                    }
                }
            }
        }

        auto fastest_route = make_vector<ll>(n, n, LINF);
        auto fastest_car = make_vector<int>(n, n, -1);
        for (int car : range(m)) {
            for (int from : range(n)) {
                for (int to : range(n)) {
                    if (umin(fastest_route[from][to], cars[car][from][to])) {
                        fastest_car[from][to] = car;
                    }
                }
            }
        }

        auto dp = make_vector<ll>(kMaxChanges + 1, n, n, LINF);
        dp[0] = fastest_route;
        for (int changes : range(n)) {
            for (int mid : range(n)) {
                for (int from : range(n)) {
                    for (int to : range(n)) {
                        const ll new_sum = dp[changes][from][mid] + fastest_route[mid][to];
                        umin(dp[changes + 1][from][to], new_sum);
                    }
                }
            }
        }

        for (int round : range(r)) {
            int from, to, changes;
            in >> from >> to >> changes;
            --from, --to;

            ll ans = LINF;
            umin(changes, n);
            for (int change : inclusiveRange(changes)) {
                umin(ans, dp[change][from][to]);
            }
            out << ans << std::endl;
        }
	}


	BAlgogonki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
