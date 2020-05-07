#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	vector<int> machines(n);
	vector<int> sockets(m);
	in >> machines >> sockets;
	vector<int> adapters(m, 0);
	vector<int> match(n, -1);

	std::set<pii> vals;
	for (int i : range(n)) {
		vals.emplace(machines[i], i);
	}

	for (int cnt_adapters : range(32)) {
		for (int i : range(m)) {
			int& power = sockets[i];
			auto it = vals.lower_bound({ power, 0 });
			if (it != vals.end() && it->first == power) {
				const int machine_id = it->second;
				match[machine_id] = i;
				adapters[i] = cnt_adapters;
				power = 0;
				vals.erase(it);
			}
			power = (power + 1) / 2;
		}
	}

	const int cnt_machines = match.size() - std::count(all(match), -1);
	const int cnt_adapters = std::accumulate(all(adapters), 0);
	out << cnt_machines << " " << cnt_adapters << endl;
	for (const auto& it : adapters) {
		out << it << " ";
	}
	out << endl;
	for (const auto& it : match) {
		out << it + 1 << " ";
	}
	out << endl;
}
