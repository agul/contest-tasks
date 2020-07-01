#include "base/header.hpp"

class FLampochkiPoKrugu {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		std::vector<bool> state(n, false);

		auto output = [&state, &out](const std::vector<int>& a) {
			out << a.size();
			for (const int x : a) {
				out << " " << x + 1;
				state[x] = true;
			}
			out << std::endl;
		};

		auto input = [&state, &in, n](const std::vector<int>& a) {
			if (a.empty()) {
				return false;
			}
			int x;
			in >> x;
			if (x == -1) {
				return false;
			}
			--x;
			for (int i : range(a.size())) {
				state[(x + i) % n] = false;
			}
			return true;
		};

		int light = 0;
		const int ans = n / 2 - 1;
		while (light < ans) {
			std::vector<int> a;
			a.reserve(n / 2);
			for (int i : range(n)) {
				if (i % 2 == 1 && !state[i]) {
					a.emplace_back(i);
				}
			}
			output(a);
			assert(input(a));
			light = std::count(all(state), true);
		}
		output({});
	}


	FLampochkiPoKrugu() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
