#include "../algolib/cpplib/base/header.hpp"
#include "../algolib/cpplib/graph/directed_graph.hpp"

class FRobotiNaPole {
public:
	void solve(std::istream& in, std::ostream& out) {
		int testsCount;
		in >> testsCount;
		for (int test : range(testsCount)) {
			in >> n >> m;
			std::vector<std::string> colors(n), field(n);
			in >> colors >> field;
			const int vertices_count = n * m;
			black = make_vector<bool>(vertices_count, false);
			graph.init(vertices_count);
			for (int i : range(n)) {
				for (int j : range(m)) {
					const int v = vertex_id(i, j);
					const Direction dir = get_direction(field[i][j]);
					black[v] = (colors[i][j] == '0');
					const int to = vertex_id(i + DX[dir], j + DY[dir]);
					graph.add_directed_edge(v, to);
				}
			}

			loop = make_vector<int>(vertices_count, -1);
			visited = make_vector<int>(vertices_count, 0);
			dist_to_loop_start = make_vector<int>(vertices_count, -1);
			loop_length.clear();
			loop_id = -1;
			for (int i : range(vertices_count)) {
				if (visited[i] == 0) {
					find_loop(i, 0);
				}
			}
			
			std::vector<pii> black_cells;
			for (int i : range(vertices_count)) {
				if (black[i]) {
					const int cur_loop = loop[i];
					black_cells.emplace_back(cur_loop, dist_to_loop_start[i] % loop_length[cur_loop]);
				}
			}
			sort(black_cells);
			unique(black_cells);

			const int max_ans = std::accumulate(all(loop_length), 0);
			const int black_ans = black_cells.size();
			out << max_ans << " " << black_ans << std::endl;
		}
	}

	int find_loop(const int v, int dist) {
		// std::cout << "DFS " << v << std::endl;
		visited[v] = 1;
		dist_to_loop_start[v] = dist;
		int& cur_len = dist_to_loop_start[v];
		int& cur_loop = loop[v];
		for (const auto& edge : graph.edges(v)) {
			const int to = edge.to();
			if (visited[to] == 0) {
				cur_len = find_loop(to, dist + 1) + 1;
				cur_loop = loop[to];
			}
			else if (visited[to] == 1) {
				loop_length.emplace_back(dist + 1 - dist_to_loop_start[to]);
				cur_loop = ++loop_id;
				cur_len = 1;
			} else {
				cur_len = dist_to_loop_start[to] + 1;
				cur_loop = loop[to];
			}
		}
		visited[v] = 2;
		return cur_len;
	}

	size_t vertex_id(const int x, const int y) const {
		return x * m + y;
	}

	Direction get_direction(const char ch) const {
		if (ch == 'U') {
			return Direction::Up;
		}
		if (ch == 'D') {
			return Direction::Down;
		}
		if (ch == 'L') {
			return Direction::Left;
		}
		if (ch == 'R') {
			return Direction::Right;
		}
		return Direction::Unknown;
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}

	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	DirectedGraph<> graph;
	std::vector<int> dist_to_loop_start;
	std::vector<int> loop;
	std::vector<int> loop_length;
	std::vector<int> visited;
	std::vector<bool> black;
	int n;
	int m;
	int loop_id;
};
