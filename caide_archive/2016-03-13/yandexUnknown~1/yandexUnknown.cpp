#include "Head.h"
#include "IO/IO.h"
#include "Maths.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000009;
const int MAXN = 111111;

const int N = 4;
const int MAX_MASK = 1 << N;

struct Point {

	std::array<int, N> x;

	Point() {
#undef fill
		x.fill(0);
	}

	void read() {
		for (auto& it : x) {
			io >> it;
		}
	}

	std::array<int, MAX_MASK> get_sums() const {
		std::array<int, MAX_MASK> result;
		result.fill(0);
		for (int mask = 0; mask < MAX_MASK; ++mask) {
			int& cur = result[mask];
			for (int i = 0; i < N; ++i) {
				if (mask & (1 << i)) {
					cur -= x[i];
				}
				else {
					cur += x[i];
				}
			}
		}
		return result;
	}

};

void solve(istream& ins, ostream& out) {
	io >> __;
	std::array<multiset<int>, MAX_MASK> diff;
	for (int _ = 0; _ < __; ++_) {
		Point x;
		int type;
		io >> type;
		x.read();
		auto vec = x.get_sums();
		if (type == 1) {
			for (int i = 0; i < MAX_MASK; ++i) {
				diff[i].insert(vec[i]);
			}
		} else
		if (type == 2) {
			for (int i = 0; i < MAX_MASK; ++i) {
				diff[i].erase(diff[i].find(vec[i]));
			}
		}
		else {
			int ans = 0;
			for (int i = 0; i < MAX_MASK; ++i) {
				umax(ans, abs(vec[i] - *diff[i].rbegin()));
			}
			io << ans << endl;
		}
	}

}
