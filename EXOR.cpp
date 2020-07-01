#include "base/header.hpp"

class EXOR {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		auto query = [&in, &out](const int x, const int y) {
			out << "? " << x + 1 << " " << y + 1 << std::endl;
			int response;
			in >> response;
			assert(response != -1);
			return response;
		};

		auto output = [&out](const std::vector<int>& ans) {
			out << "! ";
			for (int x : ans) {
				out << x << " ";
			}
			out << std::endl;
		};


		std::vector<int> a(n);
		a[0] = INF;
		for (int i : range(1, n)) {
			a[i] = query(0, i);
		}

		const int min_ind = min_element(a) - a.begin();
		const int min_value = a[min_ind];

		if (min_value == 1) {
			const bool any_even = std::any_of(all(a), [](const int x) {
				return x % 2 == 0;
			});
			if (any_even) {
				a[0] = 0;
				output(a);
				return;
			}
			a[min_ind] = 0;
			for (int i : range(n)) {
				if (i == min_ind) {
					continue;
				}
				a[i] = query(min_ind, i);
			}
			output(a);
			return;
		}



	}


	EXOR() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
