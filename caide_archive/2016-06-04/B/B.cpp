#include "Head.h"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

const int points[] = { 100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

inline int get_points(const int place) {
	if (place > 30) {
		return 0;
	}
	return points[place - 1];
}

bool check(std::vector<int>& a) {
	std::sort(all(a), greater<int>());
	return a[9] < 0;
}

void solve(istream& in, ostream& out) {
	vector<int> a(10);
	in >> a;
	for (int i = 0; i < 990; ++i) {
		a.emplace_back(a.back());
	}
	int ans = 0;
	for (int place = 1; place <= 1000; ++place) {
		std::vector<int> b = a;
		const int our = get_points(place);
		int cur = 1;
		for (int j = 9; j >= 0; --j) {
			if (cur == place) {
				++cur;
			}
			b[j] += get_points(cur++) - our;
		}
		for (int j = 10; j < 1000; ++j) {
			/* if (cur == place) {
				++cur;
			} */
			b[j] += get_points(cur++) - our;
		}
		if (check(b)) {
			ans = place;
		}
	}
	out << ans << endl;
}
