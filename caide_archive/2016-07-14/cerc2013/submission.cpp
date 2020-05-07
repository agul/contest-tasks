#pragma comment(linker, "/STACK:66777216")
#pragma warning(disable : 4996)

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#pragma hdrstop

constexpr const int INF = 0x3f3f3f3f;

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

template<typename T>
inline bool umin(T& a, const T& b) {
	return (b < a ? a = b, true : false);
}

#ifdef _MSC_VER

#endif

template<typename T, size_t N>
struct MakeVector {
	
};

template<typename T>
struct MakeVector<T, 1> {
	/// caide keep
	template<typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#include <iterator>

template<typename T>
class IntegerIterator : public std::iterator<std::input_iterator_tag, T, std::ptrdiff_t, T*, T> {
public:
	using value_type = T;

	constexpr explicit IntegerIterator(const value_type value) : value_(value) {}

	IntegerIterator& operator++() {
		++value_;
		return *this;
	}

	constexpr value_type operator*() const {
		return value_;
	}

	constexpr bool operator ==(const IntegerIterator rhs) const {
		return value_ == rhs.value_;
	}

	constexpr bool operator !=(const IntegerIterator rhs) const {
		return !(*this == rhs);
	}

private:
	value_type value_;

};

template<typename T>
class IntegerRange {
public:
	using const_iterator = IntegerIterator<T>;

	constexpr IntegerRange(const T begin, const T end) : begin_(begin), end_(end) {}

	constexpr const_iterator begin() const {
		return const_iterator(begin_);
	}

	constexpr const_iterator end() const {
		return const_iterator(end_);
	}

private:
	T begin_;
	T end_;

};

template<typename T>
constexpr IntegerRange<T> range(const T to) {
	return IntegerRange<T>(0, to);
}

using namespace std;

int __;

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
		std::priority_queue<Node> q;
		auto add_queue = [&q, &dist](const int v, const int parent, const Dist& len) {
			if (umin(dist[v], len)) {
				q.push({ len, parent, v });
			}
		};

		for (const auto& id : ids[start]) {
			add_queue(id, -1, Dist(1, 0));
		}
		while (!q.empty()) {
			const auto node = q.top();
			q.pop();
			const Dist curlen = node.dist;
			const int v = node.v;
			const int parent = node.parent;
			const int real = real_id[v];
			const int line = stop_to_line[v];
			if (dist[v] < curlen) {
				continue;
			}
			for (const auto& to : graph[real]) {
				if (real_id[to] == parent) {
					continue;
				}
				Dist newlen = curlen;
				newlen.add_stop();
				if (stop_to_line[to] != line) {
					newlen.add_line();
				}
				add_queue(to, real, newlen);
			}
		}

		Dist ans;
		for (const auto& id : ids[finish]) {
			umin(ans, dist[id]);
		}

		out << "optimal travel from " << start_stop << " to " << finish_stop << ": " << ans << endl;
	}
}

#include <fstream>

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}

