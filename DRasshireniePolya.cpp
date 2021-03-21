#include "base/header.hpp"

class DRasshireniePolya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	const ll MAXN = 111111;

	void solve(std::istream& in, std::ostream& out) {
        ll a, b, h, w;
        int n;
        in >> a >> b >> h >> w >> n;
        std::vector<ll> p(n);
        in >> p;

        sort(p, std::greater<>());
        while (p.size() > 36) {
            p.pop_back();
        }

        auto find_solution = [&p, this](const int a, const int b, int h, int w) {

            auto extend = [this](const ll width, const ll multiplier) {
                return std::min<ll>(MAXN, width * multiplier);
            };

            auto dp = make_vector<ll>(p.size() + 1, MAXN + 1, 0);
            dp[0][h] = w;
            for (int i : range(p.size())) {
                for (int j : range(MAXN)) {
                    if (dp[i][j] == 0) {
                        continue;
                    }
                    umax(dp[i + 1][j], extend(dp[i][j], p[i]));
                    umax(dp[i + 1][extend(j, p[i])], dp[i][j]);
                }
            }

            int ans = INF;
            for (int i : range(dp.size())) {
                for (int j : range(dp.front().size())) {
                    if (j >= a && dp[i][j] >= b) {
                        umin(ans, i);
                    }
                }
            }
            return ans;
        };

        int ans = std::min(find_solution(a, b, h, w), find_solution(b, a, h, w));
        out << (ans == INF ? -1 : ans) << std::endl;
	}


	DRasshireniePolya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
