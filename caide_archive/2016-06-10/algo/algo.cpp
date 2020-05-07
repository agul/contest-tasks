#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(istream& in, ostream& out) {
	int ls, n;
	string s;
	in >> ls >> n >> s;
	vector<pair<string, int>> actors(n);
	for (auto& it : actors) {
		int x;
		in >> x >> it.second >> it.first;
	}
	vector<int> dp(ls + 1, INF);
	dp[0] = 0;
	for (int i = 1; i <= ls; ++i) {
		for (int j = 0; j < i; ++j) {
			const int len = i - j;
			const std::string sub = s.substr(j, len);
			int cost = INF;
			for (const auto& it : actors) {
				if (it.first.find(sub) != std::string::npos) {
					umin(cost, it.second);
				}
			}
			if (cost == INF) {
				continue;
			}
			umin(dp[i], dp[j] + len * cost);
		}
	}
	out << (dp[ls] == INF ? -1 : dp[ls]) << endl;
}
