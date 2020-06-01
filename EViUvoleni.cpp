#include "base/header.hpp"
#include "base/functors/min.hpp"
#include "data_structures/segment_tree/top_down_segment_tree.hpp"

class EViUvoleni {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

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

	using SegmentTree = TopDownSegmentTree<ll, Min, ll, ApplyUpdate, MergeUpdates>;

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		const int k = n / 2;
		const int m = (n + 1) / 2;
		std::vector<ll> a(m);
		in >> a;

		ll x;
		in >> x;

		ll sum = std::accumulate(all(a), 0LL);
		if (n % 2 == 0) {
			sum += x;
		}

		std::vector<ll> processed(m);
		for (int i : range(m)) {
			processed[i] = sum;
			sum -= a[i];
			sum += x;
		}

		int ans = -1;

		SegmentTree min_tree(m, LINF);
		min_tree.build(processed);
		// debug(processed);
		for (int cur_size : inclusiveRange(k + 1, n)) {
			const int left = 0;
			const int right = n - cur_size;
			// debug(cur_size, left, right);
			if (min_tree.get(left, right) > 0) {
				ans = cur_size;
			}
			min_tree.range_update(left, right, x);
		}
		out << ans << std::endl;
	}


	EViUvoleni() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		int n;
		in >> n;

		const int k = (n + 1) / 2;
		std::vector<ll> a(k);
		in >> a;

		ll x;
		in >> x;

		for (int i : range(n / 2 + 1)) {
			a.emplace_back(x);
		}

		std::vector<ll> prefs = {0};
		for (ll cur : a) {
			prefs.emplace_back(prefs.back() + cur);
		}

		std::set<int> good;
		for (int size : range(1, n + 1)) {
			bool ok = true;
			for (int ending : range(size, n + 1)) {
				ok &= (prefs[ending] - prefs[ending - size] > 0);
			}
			if (ok) {
				good.emplace(size);
			}
		}

		int pans;
		out >> pans;

		if (pans == -1) {
			if (!good.empty()) {
				const int jans = *good.begin();
				debug("FAIL participant did not find answer", jans);
				return false;
			}
			return true;
		}

		if (good.find(pans) == good.cend()) {
			const int jans = *good.begin();
			debug(pans, jans);
			return false;
		}
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
		const int kMaxn = 100;
		const int kMaxm = 100;

		const int n = Random::get(2, kMaxn);
		const int k = (n + 1) / 2;
		const int x = Random::get(-kMaxm, kMaxm);

		test << n << std::endl;
		for (int i : range(k)) {
			test << Random::get(-kMaxm, kMaxm) << " ";
		}
		test << std::endl;

		test << x << std::endl;


	}

};
