#include "base/header.hpp"

class DOcherednayaIgraSChislami {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	template<typename T>
	using vector2d = std::vector<std::vector<T>>;

    template<typename T>
    using vector3d = std::vector<std::vector<std::vector<T>>>;

	bool go(vector2d<int>& dp, int x, int y) {
	    if (x > y) {
	        std::swap(x, y);
	    }
	    if (dp[x][y] != -1) {
	        return dp[x][y] == 1;
	    }
	    bool any_lose = false;

	    for (int i : inclusiveRange(1, x)) {
	        any_lose |= !go(dp, x - i, y);
	        any_lose |= !go(dp, x, y - i);
	        any_lose |= !go(dp, x - i, y - i);
	    }
	    for (int i = x + 1; i <= y; ++i) {
	        any_lose |= !go(dp, x, y - i);
	    }
	    dp[x][y] = (any_lose ? 1 : 0);
	    return any_lose;
	}

	bool go(vector3d<int>& dp, int xx, int yy, int zz) {
	    int x = std::min({xx, yy, zz});
	    int z = std::max({xx, yy, zz});
	    int y = xx + yy + zz - x - z;

        if (dp[x][y][z] != -1) {
            return dp[x][y][z] == 1;
        }
        bool any_lose = false;

        for (int i : inclusiveRange(1, x)) {
            any_lose |= !go(dp, x - i, y, z);
            any_lose |= !go(dp, x, y - i, z);
            any_lose |= !go(dp, x, y, z - i);
            any_lose |= !go(dp, x - i, y - i, z - i);
        }
        for (int i = x + 1; i <= y; ++i) {
            any_lose |= !go(dp, x, y - i, z);
            any_lose |= !go(dp, x, y, z - i);
        }
        for (int i = y + 1; i <= z; ++i) {
            any_lose |= !go(dp, x, y, z - i);
        }
        dp[x][y][z] = (any_lose ? 1 : 0);
        return any_lose;
	}

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<int> a(n);
        in >> a;
        sort(a);

        if (n == 1) {
            out << (a[0] > 0 ? "BitLGM" : "BitAryo") << std::endl;
            return;
        }
        if (n == 2) {
            auto dp = make_vector<int>(a[0] + 1, a[1] + 1, -1);
            dp[0][0] = 0;
            const bool ans = go(dp, a[0], a[1]);
            out << (ans ? "BitLGM" : "BitAryo") << std::endl;
            for (int i : inclusiveRange(a[0])) {
                for (int j : inclusiveRange(a[1])) {
                    if (dp[i][j] == 0) {
                        debug(i, j);
                    }
                }
            }
            return;
        }
        const bool ans = (a[0] ^ a[1] ^ a[2]) != 0;
        out << (ans ? "BitLGM" : "BitAryo") << std::endl;
        /*
        auto dp = make_vector<int>(a[0] + 1, a[1] + 1, a[2] + 1, -1);
        dp[0][0][0] = 0;
        const bool ans = go(dp, a[0], a[1], a[2]);
        out << (ans ? "BitLGM" : "BitAryo") << std::endl;
        for (int i : inclusiveRange(a[0])) {
            for (int j : inclusiveRange(a[1])) {
                for (int k : inclusiveRange(a[2])) {

                    if (dp[i][j][k] == 0 && (i ^ j ^ k) != 0) {
                        debug("not zero", i, j, k);
                    } else
                    if ((i ^ j ^ k) == 0 && dp[i][j][k] == 1){
                        debug("zero", i, j, k, dp[i][j][k]);
                    }
                }
            }
        }
        */

	}


	DOcherednayaIgraSChislami() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
