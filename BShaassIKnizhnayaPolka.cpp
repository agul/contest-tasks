#include "base/header.hpp"

class BShaassIKnizhnayaPolka {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve_dp(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<pii> books;
        for (int i : range(n)) {
            int t, w;
            in >> t >> w;
            books.emplace_back(w, t);
        }
        sort(books, std::greater<>());

        const int MAXN = 222;

        auto dp = make_vector<int>(MAXN, MAXN, -1);
        dp[0][0] = 0;
        for (const auto& book : books) {
            for (int i : downrange(MAXN)) {
                for (int j : downrange(MAXN)) {
                    if (dp[i][j] == -1) {
                        continue;
                    }
                    if (i + book.second < MAXN) {
                        umax(dp[i + book.second][j], dp[i][j] + 1);
                    }
                    if (j + book.first < MAXN) {
                        umax(dp[i][j + book.first], dp[i][j] + 1);
                    }
                }
            }
        }
        int ans = INF;
        for (int i : range(MAXN)) {
            for (int j : inclusiveRange(i)) {
                if (dp[i][j] == n) {
                    umin(ans, i);
                }
            }
        }
        out << ans << std::endl;
	}

    void solve_greedy(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> thin, thick;
        for (int i : range(n)) {
            int t, w;
            in >> t >> w;
            (t == 1 ? thin : thick).emplace_back(w);
        }
        sort(thin, std::greater<>());
        sort(thick, std::greater<>());

        auto suffix_sum = [](const std::vector<int>& a) {
            std::vector<int> suffix_sum(a.size() + 1, 0);
            for (int i : downrange(a.size())) {
                suffix_sum[i] = suffix_sum[i + 1] + a[i];
            }
            return suffix_sum;
        };

        std::vector<int> thin_suffix_sum = suffix_sum(thin);
        std::vector<int> thick_suffix_sum = suffix_sum(thick);


        int ans = INF;
        for (int i : inclusiveRange(thin.size())) {
            for (int j : inclusiveRange(thick.size())) {
                const int cur_thickness = i * 1 + j * 2;
                const int total_width = thin_suffix_sum[i] + thick_suffix_sum[j];
                if (total_width <= cur_thickness) {
                    umin(ans, cur_thickness);
                }
            }
        }
        out << ans << std::endl;
    }

    void solve(std::istream& in, std::ostream& out) {
	    solve_greedy(in, out);
	}


	BShaassIKnizhnayaPolka() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
