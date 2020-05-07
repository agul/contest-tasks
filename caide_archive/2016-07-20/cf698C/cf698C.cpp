#include "base/header.hpp"
#include "stack.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 10;

int n, k;
std::vector<double> p;
std::vector<Stack<int>> used;
std::vector<double> ans;

void go(const int pos, const double prob) {
	if (pos == MAXN) {
		std::vector<pii> times;
		for (int i : range(n)) {
			if (used[i].empty()) {
				continue;
			}
			times.emplace_back(used[i].top(), i);
		}
		sort(times);
		reverse(times);
		for (int i : range(min(k, (int)times.size()))) {
			ans[times[i].second] += prob;
		}
		return;
	}
	for (int i : range(n)) {
		used[i].push(pos);
		go(pos + 1, prob * p[i]);
		used[i].pop();
	}
}

void solve(std::istream& in, std::ostream& out) {
	in >> n >> k;
	p.resize(n);
	used.assign(n, Stack<int>(MAXN));
	ans.assign(n, 0);
	in >> p;
	go(0, 1);
	out << fixed << setprecision(16);
	for (const auto& it : ans) {
		out << it << " ";
	}
	out << endl;
}
