#include "base/header.hpp"

class KSmallestSums {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct State {
	    int sum;
	    std::vector<int> pos;

	    bool operator <(const State& rhs) const {
	        return sum < rhs.sum || sum == rhs.sum && pos < rhs.pos;
	    }
	};

	void solve(std::istream& in, std::ostream& out) {
        int k;
        while (in >> k) {
            auto a = make_vector<int>(k, k, 0);
            in >> a;
            int min_sum = 0;
            for (auto& vec : a) {
                sort(vec);
                min_sum += vec.front();
            }
            std::set<State> states;
            states.emplace(State{min_sum, std::vector<int>(k, 0)});
            for (int i : range(k)) {
                const State& cur = *states.begin();
                int sum = cur.sum;
                out << sum << " ";
                auto vec = cur.pos;
                for (int j : range(k)) {
                    if (vec[j] + 1 == a[j].size()) {
                        continue;
                    }
                    int new_sum = sum - a[j][vec[j]];
                    ++vec[j];
                    new_sum += a[j][vec[j]];
                    states.emplace(State{new_sum, vec});
                    --vec[j];
                }
                states.erase(states.begin());
                while (states.size() > k) {
                    states.erase(std::prev(states.end()));
                }
            }
            out << std::endl;
        }
	}


	KSmallestSums() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
