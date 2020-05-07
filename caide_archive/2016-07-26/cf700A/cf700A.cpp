#include "base/header.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

void solve(std::istream& in, std::ostream& out) {
	out << fixed << setprecision(16);
	double l, pupil_velocity, bus_velocity;
	int n, k;
	in >> n >> l >> pupil_velocity >> bus_velocity >> k;
	if (bus_velocity <= pupil_velocity + EPS) {
		out << l / pupil_velocity << endl;
		return;
	}
	const int runs = (n - 1) / k + 1;
	double L = 0, R = l;
	for (int iter = 0; iter < 100; ++iter) {
		double dist = (L + R) / 2;
		const double forward_time = dist / bus_velocity;
		const double pupil_walk = forward_time * pupil_velocity;
		const double remaining_dist = dist - pupil_walk;
		const double common_velocity = bus_velocity + pupil_velocity;
		const double time_to_meet = remaining_dist / common_velocity;
		const double dist_to_meet = time_to_meet * bus_velocity;
		if (dist + (runs - 1) * (dist - dist_to_meet) > l) {
			R = dist;
		}
		else {
			L = dist;
		}
	}
	double ans = L / bus_velocity + (l - L) / pupil_velocity;
	out << ans << endl;

}
