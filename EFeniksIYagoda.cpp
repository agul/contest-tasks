#include "base/header.hpp"

class EFeniksIYagoda {
public:

	struct Triple {
		ll cnt;
		int red;
		int blue;
	};

	void solve(std::istream& in, std::ostream& out) {
		int n, k;
		in >> n >> k;
		auto a = make_vector<pll>(n, pll{0, 0});
		in >> a;
		const ll MAGIC = 20;
		const ll kMAGIC = k * MAGIC;

		auto dp = make_vector<ll>(2, k, k, -1);
		dp[1][0][0] = 0;
		auto way = make_vector<ll>(k, k, 0);

		ll ans = 0;
		for (int i : range(n)) {
			const int cur = i & 1;
			const int prev = cur ^ 1;
			for (int x : range(k)) {
				for (int y : range(k)) {
					way[x][y] = -1;
					dp[cur][x][y] = -1;
				}
			}
			// debug("OK");
			int cur_red = a[i].X % kMAGIC;
			int cur_blue = a[i].Y % kMAGIC;
			ll cur_cnt = (a[i].X / kMAGIC + a[i].Y / kMAGIC) * MAGIC;
			for (int red : range(MAGIC)) {
				if (cur_red < red * k) {
					break;
				}
				for (int blue : range(MAGIC)) {
					if (cur_blue < blue * k) {
						break;
					}
					const ll new_cnt = cur_cnt + red + blue;
					const int new_red = cur_red - red * k;
					const int new_blue = cur_blue - blue * k;
					for (int red_rem : range(k)) {
						if (red_rem > new_red) {
							break;
						}
						const ll mixed_pile = new_red + new_blue - red_rem;
						const int blue_rem = mixed_pile % k;
						if (blue_rem > new_blue) {
							continue;
						}
						const ll new_new_cnt = new_cnt + mixed_pile / k;
						umax(way[red_rem][blue_rem], new_new_cnt);
					}
				}
			}
			std::vector<Triple> options;
			for (int x : range(k)) {
				for (int y : range(k)) {
					if (way[x][y] >= 0) {
						options.emplace_back(Triple{way[x][y], x, y});
						debug(i, way[x][y], x, y);
					}
				}
			}
			for (int x : range(k)) {
				for (int y : range(k)) {
					if (dp[prev][x][y] != -1) {
						for (const auto& option : options) {
							int new_x = x + option.red;
							int new_y = y + option.blue;
							ll new_cnt = dp[prev][x][y] + option.cnt;
							// debug(new_x, new_y, new_cnt);
							if (new_x >= k) {
								new_cnt++;
								new_x %= k;
							}
							if (new_y >= k) {
								new_cnt++;
								new_y %= k;
							}
							umax(dp[cur][new_x][new_y], new_cnt);
							umax(ans, new_cnt);
						}
					}
				}
			}

		}

		out << ans << std::endl;

	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		while (!actual_output.empty() && isspace(*--actual_output.end()))
			actual_output.erase(--actual_output.end());
		return actual_output == "1000000000000";
	}


	static constexpr size_t kGeneratedTestsCount = 1;
	static void generate_test(std::ostream& test) {
		test << "500 1" << std::endl;
		for (int i : range(500)) {
			test << "1000000000 1000000000" << std::endl;
		}
	}

private:
	size_t test_id_ = 0;
};
