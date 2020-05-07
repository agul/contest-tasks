#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

template<typename T>
class Point {
public:

	Point() : Point(0, 0) {}
	Point(const T x, const T y) : x_(x), y_(y) {}

	T x() const {
		return x_;
	}

	T y() const {
		return y_;
	}

	void read() {
		io >> x_ >> y_;
	}

	T sqr_dist(const Point& rhs) const {
		return sqr(x_ - rhs.x_) + sqr(y_ - rhs.y_);
	}

	double dist(const Point& rhs) const {
		return sqrt(sqr_dist(rhs));
	}

private:
	T x_;
	T y_;

};

void solve(istream& ins, ostream& out) {
	Point<ll> a, b, t;
	a.read();
	b.read();
	t.read();
	int n;
	io >> n;
	vector<Point<ll>> p(n);
	using pdi = std::pair<double, int>;
	vector<pdi> da(n), db(n);
	vector<double> dt(n);
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		auto& it = p[i];
		it.read();
		double to_trash = it.dist(t);
		dt[i] = to_trash;
		da[i] = { to_trash - it.dist(a), i };
		db[i] = { to_trash - it.dist(b), i };
		sum += to_trash;
	}
	out << fixed << setprecision(16);
	sort(all(da), greater<pdi>());
	sort(all(db), greater<pdi>());
	double ans = LINF;
	if (n > 1) {
		if (da[0].second == db[0].second) {
			double x = da[0].first + db[1].first;
			double y = da[1].first + db[0].first;
			{
				double dist_from_a = p[da[0].second].dist(a);
				double dist_from_b = p[db[1].second].dist(b);
				double to_trash_sum = dt[da[0].second] + dt[db[1].second];
				umin(ans, dist_from_a + dist_from_b + 2 * sum - to_trash_sum);
			}
			{
				double dist_from_a = p[da[1].second].dist(a);
				double dist_from_b = p[db[0].second].dist(b);
				double to_trash_sum = dt[da[1].second] + dt[db[0].second];
				umin(ans, dist_from_a + dist_from_b + 2 * sum - to_trash_sum);
			}
		}
		else {
			double dist_from_a = p[da[0].second].dist(a);
			double dist_from_b = p[db[0].second].dist(b);
			double to_trash_sum = dt[da[0].second] + dt[db[0].second];
			umin(ans, dist_from_a + dist_from_b + 2 * sum - to_trash_sum);
		}
	}
	{
		double dist_from_a = p[da[0].second].dist(a);
		double to_trash = dt[da[0].second];
		umin(ans, dist_from_a + 2 * sum - to_trash);
	}
	{
		double dist_from_b = p[db[0].second].dist(b);
		double to_trash = dt[db[0].second];
		umin(ans, dist_from_b + 2 * sum - to_trash);
	}
	out << ans << endl;
}
