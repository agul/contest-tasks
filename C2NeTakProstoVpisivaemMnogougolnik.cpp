#include "base/header.hpp"
#include "maths/maths.hpp"

class C2NeTakProstoVpisivaemMnogougolnik {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	long double apothem(const int n) {
		return 0.5 / std::tan(PI / n);
	}

	long double max_diagonal(const int n) {
		return 2 * std::sqrt(sqr(apothem(n)) + sqr(0.5));
		// return 0.5 / std::sin(PI / (2 * n));
	}

	void solve(std::istream& in, std::ostream& out) {
		/* const double pi = 3.14159265358979323846;
		double a = 1;

		for (int i = 0; i < 6; i++)
		{
			double x, y;
			double angle_rad = pi / 3 * i - pi / 6;
			x = cos(angle_rad);
			y = sin(angle_rad);
			out << std::fixed << std::setprecision(20) << "(" << x << "; " << y << ")" << std::endl;
		} */
		int n;
		in >> n;
		n *= 2;
		long double hypot = max_diagonal(n);
		debug(hypot);

		long double angle = PI / n * (n - 2) / 4;
		debug(angle);
		long double x = std::cos(angle) * hypot;
		long double y = std::sin(angle) * hypot;

		long double ans = (x + y) / std::sqrt(2);

		out << std::fixed << std::setprecision(20) << ans << std::endl;
	}


	C2NeTakProstoVpisivaemMnogougolnik() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
