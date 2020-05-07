#include "base/header.hpp"
#include "queue.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

std::string next_token(istream& in) {
	std::string tmp;
	in >> tmp;
	return tmp;
}

std::vector<std::string> read_tokens(istream& in) {
	std::vector<std::string> res;
	std::string buffer;
	getline(in, buffer);
	std::stringstream ss;
	ss << buffer;
	std::string tmp;
	while (ss >> tmp) {
		res.emplace_back(tmp);
	}
	return res;
}

using Map = std::unordered_map<std::string, int>;

Map read_stops(istream& in) {
	auto tokens = read_tokens(in);
	Map stops;
	for (int i = 1; i < tokens.size(); ++i) {
		auto& it = tokens[i];
		if (it.back() == ',') {
			it.pop_back();
		}
		stops[it] = stops.size();
	}
	return stops;
}

std::vector<int> read_route(const Map& stops, istream& in) {
	auto tokens = read_tokens(in);
	std::vector<int> res;
	for (int i = 1; i < tokens.size(); ++i) {
		auto& it = tokens[i];
		if (it.back() == ',') {
			it.pop_back();
		}
		res.emplace_back(stops.at(it));
	}
	return res;
}

int get_line(const Map& lines, istream& in) {
	const std::string name = next_token(in);
	return lines.at(name);
}

std::string read_person(istream& in) {
	auto tokens = read_tokens(in);
	return tokens.back();
}

struct Dist {
	int lines_count;
	int stops_count;

	Dist() : Dist(INF, -INF) {}
	Dist(const int lines, const int stops) : lines_count(lines), stops_count(stops) {}

	bool operator <(const Dist& rhs) const {
		return lines_count < rhs.lines_count || (lines_count == rhs.lines_count && stops_count > rhs.stops_count);
	}

	bool operator ==(const Dist& rhs) const {
		return lines_count == rhs.lines_count && stops_count == rhs.stops_count;
	}

	void add_line() {
		lines_count += 1;
	}

	void add_stop() {
		stops_count += 1;
	}

	static std::string ending(const int val) {
		if (val == 1) {
			return "";
		}
		return "s";
	}

	friend ostream& operator <<(ostream& out, const Dist& rhs) {
		out << rhs.lines_count << " line" << ending(rhs.lines_count) << ", " << rhs.stops_count << " minute" << ending(rhs.stops_count);
		return out;
	}

};

struct Node {
	Dist dist;
	int parent;
	int v;

	Node() : Node(Dist(), -1, 0) {}
	Node(const Dist& dist, const int parent, const int v) : dist(dist), parent(parent), v(v) {}

	bool operator <(const Node& rhs) const {
		return rhs.dist < dist || (rhs.dist == dist && parent < rhs.parent)
			|| (rhs.dist == dist && parent == rhs.parent && v < rhs.v);
	}
};

void solve(std::istream& in, std::ostream& out) {
	in >> __;
	read_tokens(in);
	for (int _ : range(__)) {
		read_tokens(in);
		auto stops = read_stops(in);
		auto lines = read_stops(in);
		const int lines_count = lines.size();
		const int stops_count = stops.size();
		std::vector<std::vector<int>> graph(stops_count);
		std::vector<std::vector<int>> ids(stops_count);
		std::vector<int> stop_to_line;
		std::vector<int> real_id;
		int cnt = 0;
		for (int i : range(lines_count)) {
			const int line = get_line(lines, in);
			const auto route = read_route(stops, in);
			int last = -1;
			int last_real = -1;
			for (const auto& stop : route) {
				ids[stop].emplace_back(cnt);
				stop_to_line.emplace_back(line);
				real_id.emplace_back(stop);
				if (last != -1) {
					graph[stop].emplace_back(last);
					graph[last_real].emplace_back(cnt);
				}
				last = cnt;
				last_real = stop;
				++cnt;
			}
		}
		const std::string start_stop = read_person(in);
		const std::string finish_stop = read_person(in);
		const int start = stops.at(start_stop);
		const int finish = stops.at(finish_stop);
		
		std::vector<Dist> dist(cnt);

		Queue<pii> q(cnt);
		auto add_queue = [&dist](Queue<pii>& q, const int v, const int parent, const Dist& len) {
			if (umin(dist[v], len)) {
				q.push({ v, parent });
			}
		};
		for (const auto& id : ids[start]) {
			add_queue(q, id, -1, Dist(1, 0));
		}

		Queue<pii> tmpq(cnt);
		Queue<pii> newq(cnt);
		for (const auto& it : q.data()) {
			tmpq.clear();
			int v = it.first;
			int p = it.second;
			int real = real_id[v];
			int line = stop_to_line[v];
			for (const auto& to : graph[real]) {
				if (to == p) {
					continue;
				}
				int to_line = stop_to_line[to];
				if (line == to_line) {
					Dist newlen = dist[v];
					newlen.add_stop();
					add_queue(tmpq, to, v, newlen);
				}
				else {
					Dist newlen
				}
			}
		}

		Dist ans;
		for (const auto& id : ids[finish]) {
			umin(ans, dist[id]);
		}

		out << "optimal travel from " << start_stop << " to " << finish_stop << ": " << ans << endl;
	}
}
