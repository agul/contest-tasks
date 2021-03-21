#include "base/header.hpp"
#include "maths/maths.hpp"

class DMalenkiiArtyomkaISluchainieVelichini {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        std::vector<double> max(n), min(n);
        in >> max >> min;

        double suma = 0;
        double sumb = 0;
        std::vector<double> A(n), B(n);
        for (int i : range(n)) {
            const double M = max[i] + min[i];

            const double a = -1;
            const double b = M - suma + sumb;
            const double c = -max[i] + M * suma;

            double x1, x2;
            solve_quadratic_equation(a, b, c, x1, x2);

            A[i] = x1;
            B[i] = M - x1;

            suma += A[i];
            sumb += B[i];
        }

        for (const double x : A) {
            out << x << " ";
        }
        out << std::endl;
        for (const double x : B) {
            out << x << " ";
        }
        out << std::endl;

	}


	DMalenkiiArtyomkaISluchainieVelichini() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
