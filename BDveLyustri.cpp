#include "base/header.hpp"
#include "maths/maths.hpp"

class BDveLyustri {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	const int MAXN = 1111111;

	bool min_positive_diophantine_solution(const ll a, const ll b, const ll c, ll& x) {
	    ll y, g;
	    if (!solve_diophantine(a, b, c, x, y, g)) {
	        return false;
	    }

        const ll bg = std::abs(b / g);
        x = (x % bg + bg) % bg;

	    return true;
	}

	void solve(std::istream& in, std::ostream& out) {
        ll n, m, k;
        in >> n >> m >> k;
        std::vector<ll> a(n), b(m);
        in >> a >> b;

        std::vector<pll> positions(MAXN, pll{-1, -1});
        for (int i : range(n)) {
            positions[a[i]].first = i + 1;
        }
        for (int i : range(m)) {
            positions[b[i]].second = i + 1;
        }

        const ll loop_len = lcm(n, m);
        std::vector<ll> first_intersection;
        for (int i : range(MAXN)) {
            if (positions[i].first == -1 || positions[i].second == -1) {
                continue;
            }

            const ll diff = positions[i].first - positions[i].second;
            ll x;
            if (!min_positive_diophantine_solution(-n, m, diff, x)) {
                continue;
            }
            ll pos = n * x + positions[i].first;
            if (pos > loop_len) {
                pos %= loop_len;
            }
            first_intersection.emplace_back(pos);
        }
        sort(first_intersection);

        debug(first_intersection);

        ull L = 0;
        ull R = 9e18;
        while (R - L > 1) {
            const ull diff = (R - L) / 2;
            const ull md = L + diff;
            ull cnt = 0;
            const ull left = md % loop_len;
            const ull loops_cnt = md / loop_len;

            const auto it = std::upper_bound(all(first_intersection), left);
            const int index = it - first_intersection.begin();
            cnt = md - loops_cnt * first_intersection.size() - index;

            if (cnt < k) {
                L = md;
            } else {
                R = md;
            }
        }
        out << R << std::endl;
	}


	BDveLyustri() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
