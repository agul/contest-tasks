#include "Head.h"
#include "IO/IO.h"
#include "Graph/Graph.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

int cnt[MAXN];
Graph graph(MAXN, MAXN);

void solve(istream& ins, ostream& out) {
	int n, m;
	io >> n >> m;
	graph.clear();
	graph.initGraph(n);
	fill(cnt, 0);
	vector<pii> inp;
	inp.reserve(m);
	for (int i = 0; i < m; ++i) {
		int to, from;
		io >> to >> from;
		--to, --from;
		graph.addDirectedEdge(to, from);
		++cnt[from];
		inp.emplace_back(to, from);
	}
	int root = -1;
	for (int i = 0; i < n; ++i) {
		if (cnt[i] == 0) {
			if (root == -1) {
				root = i;
			}
			else {
				io << "-1" << endl;
				return;
			}
		}
	}
	if (root == -1) {
		io << "-1" << endl;
		return;
	}
	unordered_set<pii> edges;
	for (int i = 1; i < n; ++i) {
		int nxt = -1;
		for (const auto& it : graph.edges[root]) {
			int to = graph.to[it];
			--cnt[to];
			if (cnt[to] == 0) {
				if (nxt == -1) {
					nxt = to;
				}
				else {
					io << "-1" << endl;
					return;
				}
			}
		}
		if (nxt == -1) {
			io << "-1" << endl;
			return;
		}
		edges.emplace(root, nxt);
		root = nxt;
	}
	int ans = m;
	for (int i = 0; i < m; ++i) {
		if (edges.size() == 0) {
			ans = i;
			break;
		}
		edges.erase(inp[i]);
	}
	io << ans << endl;
}
