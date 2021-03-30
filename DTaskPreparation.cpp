#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/prime.hpp"
#include "cpplib/data_structures/fenwick_tree/fenwick_tree.hpp"

class DTaskPreparation {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
#ifndef HOME
	static constexpr int kMaxn = 555555;
#else
	static constexpr int kMaxn = 155555;
#endif

	void solve(std::istream& in, std::ostream& out) {
        int n, queries_count;
        in >> n >> queries_count;
        std::vector<int> a(n);
        in >> a;

        std::vector<int> cnt(kMaxn, 0);
        for (int x : a) {
            ++cnt[x];
        }
        std::vector<int> pref(kMaxn, 0);
        for (int i : range(1, kMaxn)) {
            pref[i] = pref[i - 1] + cnt[i];
        }

        std::vector<ll> ans(kMaxn);
        for (int friends_count : range(1, kMaxn)) {
            int prev = 0;
            for (int minutes : inclusiveRange((kMaxn + friends_count - 1) / friends_count)) {
                const int max_task_len = minutes * friends_count;
                const ll count = pref[std::min(kMaxn - 1, max_task_len)] - pref[prev];
                ans[friends_count] += count * minutes;
                prev = max_task_len;
            }
        }

        std::vector<int> last_updated(kMaxn, -1);
        for (int _ : range(queries_count)) {
            int type, x;
            in >> type >> x;
            if (type == 3) {
                debug(x);
                out << ans[x] << std::endl;
                continue;
            }
            const int delta = (type == 1 ? 1 : -1);
            --x;
            const int prev = a[x];
            a[x] += delta;

            for (int div : divisors[std::min(prev, a[x])]) {
                ans[div] += delta;
            }
        }
	}

    std::vector<std::vector<int>> divisors;

	DTaskPreparation() : divisors(kMaxn) {
        for (int i : range(1, kMaxn)) {
            divisors[i] = divisors_vector(i);
            sort(divisors[i]);
        }
	}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    ll x;
	    std::vector<ll> pans;
	    while (out >> x) {
	        pans.emplace_back(x);
	    }

        std::vector<ll> jans;

        int n, queries_count;
        in >> n >> queries_count;
        debug(queries_count);
        std::vector<int> a(n);
        in >> a;
        for (int _ : range(queries_count)) {
            int type, x;
            in >> type >> x;
            if (type == 1) {
                ++a[x - 1];
            }
            else if (type == 2) {
                --a[x - 1];
            } else {
                ll ans = 0;
                for (int task : a) {
                    ans += (task + x - 1) / x;
                }
                jans.emplace_back(ans);
            }
        }

        if (pans.size() != jans.size()) {
            debug("WA", jans.size(), pans.size());
            return false;
        }

        for (int i : range(pans.size())) {
            if (pans[i] != jans[i]) {
                debug("WA", i, pans[i], jans[i]);
                return false;
            }
        }

		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kMaxCount = 100;
	    const int kMaxQueries = 100;
	    const int kMaxFriends = 100000;
	    const int kMaxValue = 100000;

	    const int n = Random::get(1, kMaxCount);
	    std::vector<int> a(n);
	    for (int i : range(n)) {
            a[i] = Random::get(1, kMaxValue);
	    }

	    const int queries = Random::get(1, kMaxQueries);
	    test << n << " " << queries << std::endl;
	    for (int x : a) {
	        test << x << " ";
	    }
	    test << std::endl;

	    for (int i : range(queries)) {
	        int type = Random::get(1, 3);
	        if (type == 3) {
	            const int friends = Random::get(1, kMaxFriends);
                test << "3 " << friends << std::endl;
                continue;
	        }
	        const int index = Random::get(0, n - 1);
	        if (a[index] == 1) {
	            type = 1;
	        }
	        else if (a[index] == kMaxValue) {
	            type = 2;
	        }
	        test << type << " " << index + 1 << std::endl;
	        if (type == 1) {
	            ++a[index];
	        }
	        else if (type == 2) {
	            --a[index];
	        }
	    }
	}

};
