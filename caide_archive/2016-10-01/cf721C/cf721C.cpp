#include "base/header.hpp"
#include "graph/directed_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 5010;

struct Node {
	ll len;
	int vertex;
	int cnt;

	Node() : Node(0, 0, 0) {}
	Node(const ll len, const int vertex, const int cnt) : len(len), vertex(vertex), cnt(cnt) {}

	bool operator < (const Node& rhs) const {
		return len > rhs.len;
	}
};

ll dist[MAXN][MAXN];
bool used[MAXN][MAXN];
priority_queue<Node> q;

void add(const ll len, const int v, const int cnt) {
	q.emplace(len, v, cnt);
}

void solve(std::istream& in, std::ostream& out) {
	int n, m, t;
	in >> n >> m >> t;
	DirectedGraph<ll, GraphType::Weighted> graph(n);
	for (int i : range(m)) {
		int from, to;
		ll weight;
		in >> from >> to >> weight;
		--from, --to;
		graph.add_directed_edge(from, to, weight);
	}
	fill(used, false);
	fill(dist, LINF);
	dist[0][1] = 0;
	add(0, 0, 1);
	while (!q.empty()) {
		auto it = q.top();
		q.pop();
		const int v = it.vertex;
		const int cnt = it.cnt;
		if (it.len > dist[v][cnt]) {
			continue;
		}
		for (const auto& edge : graph.edges(v)) {
			const int to = edge.to();
			const ll new_len = it.len + edge.weight();
			if (umin(dist[to][cnt + 1], new_len)) {
				add(new_len, to, cnt + 1);
			}
		}
	}
	int ans = 0;
	for (int i : range(n)) {
		if (dist[n - 1][i] <= t) {
			ans = i;
		}
	}
	vector<int> res;
	int cur_index = n - 1;
	int cur_cnt = ans;
	auto gr = graph.reversed();
	do {
		res.emplace_back(cur_index);
		const ll cur_dist = dist[cur_index][cur_cnt];
		for (const auto& it : gr.edges(cur_index)) {
			const int to = it.to();
			const ll len = it.weight();
			if (dist[to][cur_cnt - 1] + len == cur_dist) {
				cur_index = to;
				--cur_cnt;
				break;
			}
		}
	} while (cur_index != 0);
	res.emplace_back(0);
	reverse(res);
	out << ans << endl;
	for (const auto& it : res) {
		out << it + 1 << " ";
	}
	out << endl;
}
