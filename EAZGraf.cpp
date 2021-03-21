#include "base/header.hpp"

class EAZGraf {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct Edge {
	    int from;
	    int to;
	    int value;

	    Edge reversed() const {
	        return Edge{to, from, value};
	    }

	    std::tuple<int, int, int> as_tuple() const {
	        return std::make_tuple(from, to, value);
	    }

	    bool operator ==(const Edge& rhs) const {
	        return as_tuple() == rhs.as_tuple();
	    }

	    bool operator <(const Edge& rhs) const {
	        return as_tuple() < rhs.as_tuple();
	    }
	};

	void solve(std::istream& in, std::ostream& out) {
        int n, m;
        in >> n >> m;

        std::unordered_set<pii> loops;
        std::unordered_set<pii> equal_loops;

        std::unordered_map<pii, char> edges;

        for (int i : range(m)) {
            char q;
            in >> q;
            if (q == '+' || q == '-') {
                int from, to;
                in >> from >> to;

                const pii edge = {from, to};
                const pii reversed_edge = {to, from};

                if (q == '-') {
                    edges.erase(edge);

                    loops.erase(edge);
                    loops.erase(pii{to, from});

                    equal_loops.erase(edge);
                    equal_loops.erase(reversed_edge);
                } else {
                    char value;
                    in >> value;
                    
                    edges[edge] = value;

                    const auto it = edges.find(reversed_edge);
                    if (it != edges.cend()) {
                        loops.emplace(edge);

                        if (it->second == value) {
                            equal_loops.emplace(edge);
                        }
                    }
                }
            } else {
                int k;
                in >> k;
                const bool ans = (k % 2 == 0 && !equal_loops.empty() || k % 2 == 1 && !loops.empty());
                out << (ans ? "YES" : "NO") << std::endl;
            }
        }
	}


	EAZGraf() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
