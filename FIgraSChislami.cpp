#include "base/header.hpp"

class FIgraSChislami {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		std::vector<pli> a;
		for (int i : range(3)) {
			ll x;
			in >> x;
			a.emplace_back(x, i + 1);
		}
		sort(a);

		int last_changed = -1;
		auto input = [&a, &in, &last_changed](const ll delta) {
			int response;
			in >> response;
			for (int i : range(3)) {
				if (a[i].second == response) {
					a[i].first += delta;
					last_changed = i;
				}
			}
			return response;
		};

		out << "First" << std::endl;

		const ll first_step = a[2].first - a[1].first;
		out << first_step << std::endl;
		if (input(first_step) <= 0) {
			return;
		}

		if (last_changed == 0) {
			const ll second_step = a[2].first - a[1].first;
			out << second_step << std::endl;
			if (input(second_step) <= 0) {
				return;
			}
		}

		const ll prelast_step = 2 * a[2].first - a[1].first - a[0].first;
		out << prelast_step << std::endl;
		if (input(prelast_step) <= 0) {
			return;
		}

		const ll last_step = a[last_changed].first - a[2].first;
		out << last_step << std::endl;
		if (input(last_step) <= 0) {
			return;
		}

		assert(false);
	}


	FIgraSChislami() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
