#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

const std::string commands[] = {"insert", "removeMin", "getMin"};
enum Command {
	insert,
	removeMin,
	getMin
};

inline Command get_command(istream& in) {
	std::string s;
	in >> s;
	for (int i = 0; i < 3; ++i) {
		if (s.front() == commands[i].front()) {
			return static_cast<Command>(i);
		}
	}
}

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<pair<Command, int>> a, ans;
	for (int i = 0; i < n; ++i) {
		Command cur = get_command(in);
		int x = 0;
		if (cur != removeMin) {
			in >> x;
		}
		a.emplace_back(cur, x);
	}
	std::priority_queue<int, std::vector<int>, std::greater<int>> b;
	for (const auto& it : a) {
		if (it.first == insert) {
			b.emplace(it.second);
			ans.emplace_back(it);
			continue;
		}
		if (it.first == removeMin) {
			if (b.empty()) {
				ans.emplace_back(insert, 0);
			}
			ans.emplace_back(it);
			if (!b.empty()) {
				b.pop();
			}
			continue;
		}
		while (!b.empty() && b.top() < it.second) {
			b.pop();
			ans.emplace_back(removeMin, 0);
		}
		if (b.empty() || b.top() != it.second) {
			ans.emplace_back(insert, it.second);
			b.emplace(it.second);
		}
		ans.emplace_back(it);
		// b.erase(b.begin());
	}
	out << ans.size() << endl;
	for (const auto& it : ans) {
		out << commands[it.first];
		if (it.first != removeMin) {
			out << " " << it.second;
		}
		out << endl;
	}
}
