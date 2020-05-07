#include "base/header.hpp"
#include "graph/undirected_graph.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
constexpr int MAXN = 55555;
constexpr int MAXK = 22;

UndirectedGraph<int> coaches;

size_t n, m;
int teams[MAXN][MAXK];
int len[MAXN];

void solve(std::istream& in, std::ostream& out) {
	srand(time(NULL));
	in >> n >> m;
	coaches = UndirectedGraph<int>(n);
	for (int i : range(m)) {
		int from, to;
		in >> from >> to;
		coaches.add_bidirectional_edge(from - 1, to - 1);
	}
	int teams_cnt = 0;
	for (int i : range(m)) {
		in >> len[i];
		for (int j : range(len[i])) {
			in >> teams[i][j];
			umax(teams_cnt, teams[i][j]);
			--teams[i][j];
		}
	}
	std::vector<int> coach_id(n);
	std::vector<int> conference(teams_cnt);
	std::vector<int> match(n);
	std::iota(all(coach_id), 0);
	bool ok = false;
	while (!ok) {
		std::random_shuffle(all(coach_id));
		conference.assign(teams_cnt, 0);
		for (int team : range(teams_cnt)) {
			conference[team] = rand() % 2;
		}
		match.assign(n, -1);
		for (int coach : coach_id) {
			vector<int> cnt(2, 0);
			for (const auto& it : coaches.edges(coach)) {
				const int to = it.to();
				const int opposite_team = match[to];
				if (opposite_team == -1) {
					continue;
				}
				cnt[conference[opposite_team]]++;
			}
			bool matched = false;
			for (int i : range(len[coach])) {
				const int team_id = teams[coach][i];
				const int conf = conference[team_id];
				if (cnt[conf] <= cnt[1 - conf]) {
					matched = true;
					match[coach] = team_id;
					break;
				}
			}
			if (!matched) {
				match[coach] = teams[coach][0];
			}
		}
		int edges = 0;
		for (int i : range(n)) {
			const int cur_team = match[i];
			const int cur_conf = conference[cur_team];
			for (const auto& it : coaches.edges(i)) {
				const int to = it.to();
				const int opposite_team = match[to];
				const int opposite_conf = conference[opposite_team];
				edges += (opposite_conf ^ cur_conf);
			}
		}
		edges /= 2;
		if (edges > m / 2) {
			for (int i : range(n)) {
				out << match[i] + 1 << " ";
			}
			out << endl;
			for (int i : range(teams_cnt)) {
				out << conference[i] + 1 << " ";
			}
			out << endl;
			break;
		}
	}
}
