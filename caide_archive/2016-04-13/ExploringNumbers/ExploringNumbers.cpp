#include "Head.h"
#include "Maths.h"

const int MOD = 1000000007;
const int MAXN = 111111;


class ExploringNumbers {
public:

	int get_sum(const int n) const {
		int x = n;
		int sum = 0;
		while (x > 0) {
			sum += sqr(x % 10);
			x /= 10;
		}
		return sum;
	}

    /// caide keep
    int numberOfSteps(const int n) {
		int last = n;
		int step;
		std::vector<bool> used(1000, false);
		for (step = 1; step <= n && !isPrime(last); ++step) {
			last = get_sum(last);
			if (used[last]) {
				break;
			}
			used[last] = true;
		}
		if (!isPrime(last)) {
			return -1;
		}
		return step;
    }
};


int solve(int n, int) {
    ExploringNumbers sol;
    return sol.numberOfSteps(n);
}
