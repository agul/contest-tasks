#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

bool check(const std::vector<int>& schedule, const std::vector<int>& prepare, const int days) {
	const int m = prepare.size();
	std::vector<int> last(m, -1);
	for (int i : range(days)) {
		const int exam = schedule[i];
		if (exam == 0) {
			continue;
		}
		last[exam - 1] = i;
	}

	int passed = 0;
	int days_spent = 0;
	std::set<pii> exams;
	for (int i : range(m)) {
		if (last[i] == -1) {
			return false;
		}
		exams.emplace(last[i], i);
	}
	while (!exams.empty()) {
		const auto exam = *exams.begin();
		exams.erase(exams.begin());
		const int date = exam.first;
		const int id = exam.second;
		days_spent += prepare[id];
		if (days_spent + passed > date) {
			return false;
		}
		++passed;
	}

	return true;
}

void solve(std::istream& in, std::ostream& out) {
	int n, m;
	in >> n >> m;
	vector<int> schedule(n);
	vector<int> prepare(m);
	in >> schedule >> prepare;
	if (!check(schedule, prepare, n)) {
		out << -1 << endl;
		return;
	}
	int L = 0, R = n;
	while (R - L > 1) {
		int md = (L + R) / 2;
		(check(schedule, prepare, md) ? R : L) = md;
	}
	out << R << endl;
}
