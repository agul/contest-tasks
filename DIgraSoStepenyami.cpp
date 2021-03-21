#include "base/header.hpp"
#include "maths/bits.hpp"

#ifdef HOME
const int kMaxDegree = 8;
#else
const int kMaxDegree = 8;
#endif

const int kMaxMask = 1 << kMaxDegree;
int8_t memo[kMaxMask];

class DIgraSoStepenyami {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	std::vector<int> mex = {0, 1, 2, 1, 4, 3, 2, 1, 5, 6, 2, 1, 8, 7, 5, 9, 8, 7, 3, 4, 7, 4, 2, 1, 10, 9, 3, 6, 11, 12, 14};

	const int MAXN = 111111;

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;

        std::vector<bool> used(MAXN, false);

        int cnt_ones = n;
        int result = 0;
        for (ll i = 2; i * i <= n; ++i) {
            if (used[i]) {
                continue;
            }
            int cur_cnt = 0;
            for (ll j = i; j <= n; j *= i) {
                if (j < MAXN) {
                    used[j] = true;
                }
                --cnt_ones;
                ++cur_cnt;
            }
            result ^= mex[cur_cnt];
        }
        result ^= (cnt_ones & 1);

        out << (result == 0 ? "Petya" : "Vasya") << std::endl;
	}


	DIgraSoStepenyami() {
	    if (mex.empty()) {
	        precalc();
	    }
	}

	int go(const int mask) {
	    if (memo[mask] != -1) {
	        return memo[mask];
	    }
	    int32_t outcomes = 0;
	    for (int i : inclusiveRange(1, kMaxDegree)) {
	        if (!test_bit(mask, i - 1)) {
	            continue;
	        }
	        int new_mask = mask;
	        for (int j = i - 1; j < kMaxDegree; j += i) {
	            new_mask &= ~(1 << j);
	        }
            outcomes |= (1 << go(new_mask));
	    }

	    for (int i : range(kMaxDegree)) {
	        if (!test_bit(outcomes, i)) {
	            memo[mask] = i;
	            return i;
	        }
	    }
	    debug("Answer for mask is not found", mask);
	    return -1;
	}

	void precalc() {
	    mex.emplace_back(0);
	    debug(sizeof(memo));
        memset(memo, -1, sizeof(memo));

        debug("Starting precalc");
        go(kMaxMask - 1);

        for (int i : inclusiveRange(1, kMaxDegree)) {
            mex.emplace_back(memo[(1 << i) - 1]);
        }

        debug(mex);
	}

	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
