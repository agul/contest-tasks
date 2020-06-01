#include "base/header.hpp"

class DKrisaKveshISir {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		long double x, y, z;
		in >> x >> y >> z;

		std::string ans = find_ans(x, y, z);

		out << ans << std::endl;

		if (false) {
			for (double x = 0.1; x <= 20.0; x += 0.1) {
				for (double y = x; y <= 20.0; y += 0.1) {
					for (double z = y; z <= 20.0; z += 0.1) {
						const std::string ans = find_ans(x, y, z);
						if (ans != "x^y^z") {
							debug(x, y, z, ans);
						}
						out << ans << std::endl;
					}
				}
			}
		}


	}

	std::string find_ans(const long double x, const ld y, const ld z) const {

		std::vector<std::string> expressions = {
				"x^y^z",
				"x^z^y",
				"(x^y)^z",
				"(x^z)^y",

				"y^x^z",
				"y^z^x",
				"(y^x)^z",
				"(y^z)^x",

				"z^x^y",
				"z^y^x",
				"(z^x)^y",
				"(z^y)^x"
		};

		auto calc = [](const long double x, const long double y) {
			return std::log(x) * y;
		};

		std::vector<std::pair<ld, ld>> pairs = {
				{x, std::pow(y, z)},
				{x, std::pow(z, y)},
				{x, y * z},
				{x, z * y},

				{y, std::pow(x, z)},
				{y, std::pow(z, x)},
				{y, z * x},
				{y, x * z},

				{z, std::pow(x, y)},
				{z, std::pow(y, x)},
				{z, y * x},
				{z, x * y}
		};

		std::vector<ld> values;
		for (const auto& it : pairs) {
			values.emplace_back(calc(it.X, it.Y));
		}

		ld best = values.front();
		std::string ans = expressions.front();
		for (int i : range(12)) {
			if (best + 1e-16 < values[i]) {
				best = values[i];
				ans = expressions[i];
			}
		}
		return ans;
	}


	DKrisaKveshISir() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

};
