#include "base/header.hpp"
#include "containers/queue/cmp_queue.hpp"
#include "maths/random.hpp"

class TestTask {
public:
	void solve(std::istream& in, std::ostream& out) {
		const int kMaxn = 100;
		CmpQueue<int> st(kMaxn);
		std::vector<int> a;

		for (int i : range(kMaxn)) {
			int x = Random::get();

			if (Random::get(3) == 0 && !st.empty()) {
				a.erase(a.begin());
				st.pop();
			}

			a.emplace_back(x);
			st.push(x);

			out << st.min_value() << " " << *std::min_element(all(a)) << std::endl;

		}

	}

	static constexpr bool kUseCustomChecker = false;
	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {}

private:
	size_t test_id_ = 0;
};
