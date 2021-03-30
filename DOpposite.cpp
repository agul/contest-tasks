#include "base/header.hpp"
#include "geometry/point_vector.hpp"
#include "maths/decimal.hpp"

class DOpposite {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Pt = Point2D<double>;

	void solve(std::istream& in, std::ostream& out) {
        int n;
        Pt first, opposite;
        in >> n >> first >> opposite;

        Pt center = (first + opposite);
        center.x /= 2;
        center.y /= 2;

        const Decimal<> r = first.dist(center);

        Pt center2 = first - center;
        const Decimal<> angle = center2.angle();


        const Decimal<> value = angle + Decimal<>::pi() * 2 / n;

        Decimal<> x = r * std::cos(value.double_value()) + center.x;
        Decimal<> y = r * std::sin(value.double_value()) + center.y;
        out << x << " " << y << std::endl;
	}


	DOpposite() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
