#include "base/header.hpp"
#include "collections/queue/queue.hpp"
#include "maths/bits.hpp"
#include "maths/maths.hpp"

class EOcherednoiTurnirSitkhov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		auto p = make_vector<ld>(n, n, 0);
		in >> p;

		std::vector<int> masks(1 << n);
		std::iota(all(masks), 0);
		sort(masks, [](const int lhs, const int rhs) {
			const int left_pc = popcount(lhs);
			const int right_pc = popcount(rhs);
			return left_pc < right_pc || (left_pc == right_pc && lhs < rhs);
		});


		auto prob_max = make_vector<ld>(1 << n, n, 0);
		auto prob_tot = make_vector<ld>(1 << n, n, 0);
		for (int i : range(n)) {
			prob_max[1 << i][i] = 1.0;
			prob_tot[1 << i][i] = 1.0;
		}

		for (int mask : masks) {
			if (popcount(mask) < 2) {
				continue;
			}
			for (int winner : range(n)) {
				if (!test_bit(mask, winner)) {
					continue;
				}

				int cnt = 0;
				ld cur_res = 0;

				for (int next_participant : range(n)) {
					if (!test_bit(mask, next_participant) || next_participant == winner) {
						continue;
					}
					const int prev_mask = mask ^ (1 << next_participant);
					cur_res += prob_tot[prev_mask][winner] * p[winner][next_participant];
					++cnt;
				}

				if (mask == 14) {
					debug(cnt, cur_res);
				}

				{
					const int prev_mask = mask ^ (1 << winner);
					const int cur_cnt = factorial(popcount(prev_mask));
					for (int prev_winner : range(n)) {
						if (!test_bit(prev_mask, prev_winner)) {
							continue;
						}
						cur_res += prob_tot[prev_mask][prev_winner] * p[winner][prev_winner];
					}
				}
				++cnt;
				if (mask == 14) {
					debug(cur_res, cnt);
				}


				prob_tot[mask][winner] = cur_res / cnt;
			}
		}

//		debug(prob_tot[6]);
//		debug(prob_tot[10]);
//		debug(prob_tot[12]);
//		debug(prob_tot[14]);

		for (int mask : masks) {
			if (popcount(mask) < 2) {
				continue;
			}
			for (int winner : range(n)) {
				if (!test_bit(mask, winner)) {
					continue;
				}

				{
					ld cur_res = 0;
					const int prev_mask = mask ^ (1 << winner);
					for (int prev_winner : range(n)) {
						if (!test_bit(prev_mask, prev_winner)) {
							continue;
						}
						cur_res += prob_tot[prev_mask][prev_winner] * p[winner][prev_winner];
					}
					debug("WINNER NEW", mask, winner, cur_res);
					umax(prob_max[mask][winner], cur_res);
				}

				for (int next_participant : range(n)) {
					if (!test_bit(mask, next_participant) || next_participant == winner) {
						continue;
					}
					const int prev_mask = mask ^ (1 << next_participant);
					ld cur_res = prob_tot[prev_mask][winner] * p[winner][next_participant];
					umax(prob_max[mask][winner], cur_res);
				}
			}
		}

		for (int mask : range(1 << n)) {
			std::string binary_mask;
			for (int i : range(n)) {
				binary_mask += '0' + (test_bit(mask, i) ? 1 : 0);
			}
			debug(binary_mask, prob_max[mask]);
		}

		const ld ans = prob_max[(1 << n) - 1][0];
		out << std::fixed << std::setprecision(16) << ans << std::endl;
	}


	EOcherednoiTurnirSitkhov() {}


	static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		ld jans;
		jury >> jans;

		ld pans;
		out >> pans;

		return std::abs(jans - pans) < EPS;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
