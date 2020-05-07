#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 100010;
const int MAXM = 1010;

using Bitset = std::bitset<1024>;

Bitset states[MAXN];
int history[MAXN][MAXM];
int history_ans[MAXN];
int current[MAXM];

void solve(std::istream& in, std::ostream& out) {
	int n, m, q;
	in >> n >> m >> q;
	fill(current, 0);
	fill(history, 0);
	states[0].reset();
	history_ans[0] = 0;
	Bitset mask;
	for (int i : range(m)) {
		mask.set(i);
	}
	int ans = 0;
	for (int step : inclusiveRange(1, q)) {
		int type;
		in >> type;
		if (type == 1) {
			int shelf, pos;
			in >> shelf >> pos;
			--shelf, --pos;
			states[step] = states[current[shelf]];
			if (!states[step][pos]) {
				states[step].set(pos);
				++ans;
				current[shelf] = step;
			}
		}
		else if (type == 2) {
			int shelf, pos;
			in >> shelf >> pos;
			--shelf, --pos;
			states[step] = states[current[shelf]];
			if (states[step][pos]) {
				--ans;
				states[step].reset(pos);
				current[shelf] = step;
			}
		}
		else if (type == 3) {
			int shelf;
			in >> shelf;
			--shelf;
			states[step] = states[current[shelf]];
			ans -= states[step].count();
			states[step].flip();
			states[step] &= mask;
			current[shelf] = step;
			ans += states[step].count();
		}
		else if (type == 4) {
			int pos;
			in >> pos;
			std::copy(history[pos], history[pos] + n, current);
			ans = history_ans[pos];
		}
		else {
			assert(false);
		}
		std::copy(current, current + n, history[step]);
		history_ans[step] = ans;
		out << ans << endl;
	}
}
