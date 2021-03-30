#include "base/header.hpp"
#include "data_structures/segment_tree/bottom_up_segment_tree.hpp"
#include "base/functors/min.hpp"

class EElektrichkiIStatistika {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n - 1);
        in >> a;

        BottomUpSegmentTree<ll> tree(n, Min(), LINF);
        tree.update(n - 1, n - 1);

        ll ans = 0;
        for (int i : downrange(n - 1)) {
            const auto best_value = tree.query(i + 1, a[i] - 1);
            const int dist_to_last = n - 1 - i;

            const ll cur_ans = best_value + dist_to_last - (a[i] - 1);
            tree.update(i, cur_ans + i);
            // debug(i, cur_ans);
            ans += cur_ans;
        }
        out << ans << std::endl;
	}


	EElektrichkiIStatistika() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    int n;
	    in >> n;
	    std::vector<int> a(n - 1);
	    in >> a;
	    a.emplace_back(n);

	    debug("checker");
	    ll jans = 0;
	    for (int i : range(n)) {
            auto dp = make_vector<int>(n, INF);
            dp[i] = 0;
            ll cur_ans = 0;
            for (int j : range(i, n)) {
                cur_ans += dp[j];
                for (int k : range(j + 1, a[j])) {
                    umin(dp[k], dp[j] + 1);
                }
            }
            // debug(i, cur_ans);
            jans += cur_ans;
	    }

	    ll pans;
	    out >> pans;

	    if (jans != pans) {
	        debug(jans, pans);
	        return false;
	    }

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kMaxn = 100;

	    const int n = Random::get(2, kMaxn);
	    test << n << std::endl;
	    for (int i : range(n - 1)) {
	        test << Random::get(i + 2, n) << " ";
	    }
	    test << std::endl;
	}

};
