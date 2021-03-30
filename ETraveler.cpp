#include "base/header.hpp"
#include "collections/value_compressor.hpp"

class ETraveler {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<pii> balls(n);
        in >> balls;

        std::vector<int> colors(n);
        for (int i : range(n)) {
            colors[i] = balls[i].second;
        }
        colors.emplace_back(0);
        colors.emplace_back(n + 1);
        sort(colors);
        IntegralValueCompressor<int> compressor(colors);
        const int colors_count = compressor.size();
        std::vector<int> max_coord(colors_count, -INF), min_coord(colors_count, INF);
        min_coord.front() = 0;
        max_coord.front() = 0;

        min_coord.back() = 0;
        max_coord.back() = 0;
        for (auto& ball : balls) {
            int& color = ball.second;
            color = compressor[color];
            umin(min_coord[color], ball.first);
            umax(max_coord[color], ball.first);
        }
        debug(min_coord);
        debug(max_coord);
        auto dp = make_vector<ll>(colors_count + 1, 2, LINF);
        dp[0] = dp[1] = {0, 0};
        for (int cur_color : range(1, colors_count)) {
            for (int end : range(2)) {
                const int x = (end == 0 ? min_coord : max_coord)[cur_color - 1];

                umin(dp[cur_color + 1][0], dp[cur_color][end] + std::abs(x - max_coord[cur_color]) + std::abs(max_coord[cur_color] - min_coord[cur_color]));
                umin(dp[cur_color + 1][1], dp[cur_color][end] + std::abs(x - min_coord[cur_color]) + std::abs(max_coord[cur_color] - min_coord[cur_color]));
            }
        }
        out << *min_element(dp.back()) << std::endl;
	}


	ETraveler() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
