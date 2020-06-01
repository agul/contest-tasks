#include "base/header.hpp"

class EShestiugolniki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		ll n;
		in >> n;

		if (n == 0) {
			out << "0 0" << std::endl;
			return;
		}

		auto grid_size = [](const ll n) {
			return n * 3 * (n + 1) + 1;
		};

		auto find_layer = [&grid_size](const ll n) {
			ll L = 0;
			ll R = 1e9;
			while (R - L > 1) {
				const ll md = (L + R) / 2;
				if (grid_size(md) < n) {
					L = md;
				} else {
					R = md;
				}
			}
			return R;
		};

		const ll layer = find_layer(n + 1);
		const ll cell_id = n - grid_size(layer - 1);

		debug(layer, cell_id);

		const ll side_id = cell_id / layer;
		const ll cell_id_in_side = cell_id % layer;

		auto get_point = [](const ll layer, const int side_id, const ll cell_id_in_side) {
			const std::vector<pll> corners = {
					{layer * 2, 0},
					{layer, layer * 2},
					{-layer, layer * 2},
					{-layer * 2, 0},
					{-layer, -layer * 2},
					{layer, -layer * 2}
			};

			const auto& a = corners[side_id];
			const auto& b = corners[(side_id + 1) % 6];

			const ll dx = (b.first - a.first) / layer;
			const ll dy = (b.second - a.second) / layer;
			return pll{a.first + dx * (cell_id_in_side + 1), a.second + dy * (cell_id_in_side + 1)};
		};

		const auto ans = get_point(layer, side_id, cell_id_in_side);
		out << ans.first << " " << ans.second << std::endl;
	}


	EShestiugolniki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
