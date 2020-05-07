#include "base/header.hpp"
#include "geometry/point_vector.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

const int MAGIC = 10;

using Pt = Point2D<ll>;

void solve(std::istream& in, std::ostream& out) {
	int n;
	in >> n;
	vector<Pt> points(n);
	in >> points;
	Pt mass;
	for (const auto& it : points) {
		mass += it;
	}
	sort(points, [](const Pt& lhs, const Pt& rhs) {
		return std::make_pair(lhs.x, lhs.y) < std::make_pair(rhs.x, rhs.y);
	});
	auto pointsY = points;
	sort(pointsY, [](const Pt& lhs, const Pt& rhs) {
		return std::make_pair(lhs.y, lhs.x) < std::make_pair(rhs.y, rhs.x);
	});
	ll xx = mass.x / n;
	ll yy = mass.y / n;

	auto dist = [&](const Pt& lhs, const ll x, const ll y) {
		return abs(lhs.x - x) + abs(lhs.y - y);
	};

	auto passY = [&](const ll x, const ll y) {
		ll posY = y - n / 2;
		ll ans = 0;
		for (int i : range(n)) {
			ans += dist(pointsY[i], x, posY);
			++posY;
		}
		return ans;
	};

	auto passX = [&](const ll x, const ll y) {
		ll posX = x - n / 2;
		ll ans = 0;
		for (int i : range(n)) {
			ans += dist(points[i], posX, y);
			++posX;
		}
		return ans;
	};

	ll ans = LINF;
	for (ll x = xx - MAGIC; x <= xx + MAGIC; ++x) {
		for (ll y = yy - MAGIC; y <= yy + MAGIC; ++y) {
			if (x == 1 && y == 2) {
				x = 1;
			}
			const ll curX = passX(x, y);
			const ll curY = passY(x, y);
			umin(ans, curX);
			umin(ans, curY);
		}
	}
	out << ans << endl;
}
