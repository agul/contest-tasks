#include "base/header.hpp"

const int MOD = 1000000007;
const int MAXN = 111111;

using namespace std;

class BearKRoads {
public:
	struct Edge {
		Edge() : Edge(0, 0, 0) {}
		Edge(int from, int to, int cnt) : from(from), to(to), cnt(cnt) { }
		
		bool operator < (const Edge& rhs) const {
			return cnt > rhs.cnt;
		}

		int from, to;
		int cnt;
	};


    /// caide keep
    int maxHappy(vector<int> x, vector<int> a, vector<int> b, int k) {
		return greedy(x, a, b, k);
    }

private:
	int greedy(vector<int> x, vector<int> a, vector<int> b, int k) {
		const int m = a.size();
		int result = 0;
		for (int i = 0; i < k; ++i) {
			std::vector<Edge> edges;
			for (int i = 0; i < m; ++i) {
				edges.emplace_back(a[i], b[i], x[a[i]] + x[b[i]]);
			}
			sort(edges);
			const auto& it = edges.front();
			result += it.cnt;
			x[it.to] = 0;
			x[it.from] = 0;
		}
		return result;
	}
};


int solve(vector<int> x, vector<int> a, vector<int> b, int K, int) {
    BearKRoads sol;
    return sol.maxHappy(x, a, b, K);
}
