#include "base/header.hpp"
#include "base/functors/max.hpp"
#include "data_structures/segment_tree/top_down_segment_tree.hpp"

class DMaksimalnayaSummaNaChetnikhPozitsiyakh {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	struct ApplyUpdate : Applier<ll> {
		ll operator()(const ll& value, const ll& update, const size_t left, const size_t right) const {
			return value + update;
		}
	};

	struct MergeUpdates : Merger<ll> {
		ll operator()(const ll& acc_updates, const ll& update) const {
			return acc_updates + update;
		}
	};

	using SegmentTree = TopDownSegmentTree<ll, Max, ll, ApplyUpdate, MergeUpdates>;

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<ll> a(n);
		in >> a;

		++n;
		a.insert(a.begin(), 0);

		std::vector<ll> odd_pos_sum(n, 0);
		for (int i : range(1, n)) {
			odd_pos_sum[i] += odd_pos_sum[i - 1] + (i % 2 == 1 ? a[i] : 0);
		}

		std::vector<ll> r_odd_pos_sum(n, 0);
		for (int i : downrange(n)) {
			r_odd_pos_sum[i] += (i + 1 < n ? r_odd_pos_sum[i + 1] : 0) + (i % 2 == 1 ? a[i] : 0);
		}

		SegmentTree even_pos(n);
		SegmentTree odd_pos(n);

		ll ans = 0;
		for (int i : downrange(n)) {
			auto& tree = (i % 2 == 1 ? odd_pos : even_pos);
			auto& opposite_tree = (i % 2 == 1 ? even_pos : odd_pos);

			const ll best_pivot = tree.get(i, n - 1);
			const ll cur_value = odd_pos_sum[i] + best_pivot;

			umax(ans, cur_value);

			if (i % 2 == 0) {
				opposite_tree.range_update(i + 1, n - 1, a[i]);
			} else {
				opposite_tree.range_update(i + 1, n - 1, a[i + 1]);
			}

			if (i < n - 1) {
				odd_pos.point_update(i, r_odd_pos_sum[i + 1]);
				even_pos.point_update(i, r_odd_pos_sum[i + 1]);
			}
		}
		out << ans << std::endl;

	}


	DMaksimalnayaSummaNaChetnikhPozitsiyakh() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
