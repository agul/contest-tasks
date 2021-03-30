#include "base/header.hpp"
#include "maths/mod_int.hpp"
#include "collections/queue/queue.hpp"

class COtrazheniyaOtPloskostei {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	using Int = ModInt<int>;

	struct Particle {
	    int dir;
	    int pos;
	    int k;
	};

	void solve(std::istream& in, std::ostream& out) {
        int n, k;
        in >> n >> k;

        /*
        std::vector<std::vector<int>> ans(9);
        Queue<Particle> q(1111111);
        for (int N : range(1, 9)) {
            for (int K : range(1, 9)) {
                int cnt = 1;
                q.clear();

                auto add = [&N, &K, &q](const int dir, const int pos, const int k) {
                    // debug(dir, pos, k);
                    q.push(Particle{dir, pos, k});
                };

                auto die = [&N, &K](const int dir, const int pos, const int k) {
                    if (pos == 0 && dir == -1 || pos == N + 1 && dir == 1 || k == 1) {
                        return true;
                    }
                    return false;
                };

                auto die_particle = [&die](const Particle& particle) {
                    return die(particle.dir, particle.pos, particle.k);
                };

                add(1, 1, K);
                while (!q.empty()) {
                    const auto particle = q.pop_front();
                    if (die_particle(particle)) {
                        continue;
                    }
                    add(particle.dir, particle.pos + particle.dir, particle.k);

                    ++cnt;
                    add(particle.dir * -1, particle.pos - particle.dir, particle.k - 1);
                }

                // debug(N, K, cnt);
                ans[K].emplace_back(cnt);
            }
        }
        for (int K : range(9)) {
            debug(K, ans[K]);
        }
         */

        auto dp = make_vector<Int>(k + 1, n, 2, 0);

        for (int power : range(1, k)) {
            std::vector<Int> left_pref(n + 1, 0);
            std::vector<Int> right_pref(n + 1, 0);
            for (int pos : range(n)) {
                left_pref[pos + 1] = left_pref[pos] + dp[power - 1][pos][1];
            }
            for (int pos : downrange(n)) {
                right_pref[pos] = right_pref[pos + 1] + dp[power - 1][pos][0];
            }
            for (int pos : range(n)) {
                dp[power][pos][0] = left_pref[pos] + 1;
                dp[power][pos][1] = right_pref[pos + 1] + 1;
            }
        }

        Int ans = 1;
        for (int pos : range(n)) {
            ans += dp[k - 1][pos][0];
        }
        out << ans << std::endl;
	}


	COtrazheniyaOtPloskostei() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
