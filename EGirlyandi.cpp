#include "base/header.hpp"
#include "data_structures/fenwick_tree/fenwick_tree_2d.hpp"
#include "geometry/point_vector.hpp"

class EGirlyandi {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using Pt = Point2D<int>;

	struct Lamp {
        Pt position;
        ll weight;

        friend std::istream& operator>>(std::istream& in, Lamp& lamp) {
            return in >> lamp.position >> lamp.weight;
        }
	};

	struct Query {
	    enum Type {
	        Switch,
	        Ask
	    };

	    Type type;
	    int id;
	};

	using Garland = std::vector<Lamp>;
	using AskQuery = std::pair<Pt, Pt>;

	const std::string kAskQuery = "ASK";

	void solve(std::istream& in, std::ostream& out) {
        int n, m, garlands_count;
        in >> n >> m >> garlands_count;

        std::vector<Garland> garlands(garlands_count);
        for (auto& garland : garlands) {
            int size;
            in >> size;
            garland.resize(size);
            in >> garland;
        }

        int queries_count;
        in >> queries_count;

        std::vector<Query> queries(queries_count);
        std::vector<AskQuery> ask_queries;
        for (auto& query : queries) {
            std::string query_type;
            in >> query_type;
            if (query_type == kAskQuery) {
                AskQuery ask_query;
                in >> ask_query;

                const int query_id = ask_queries.size();
                query = {Query::Type::Ask, query_id};
                ask_queries.emplace_back(ask_query);
            } else {
                int garland_id;
                in >> garland_id;
                --garland_id;
                query = {Query::Type::Switch, garland_id};
            }
        }

        const int ask_queries_count = ask_queries.size();
        auto weight_sum = make_vector<ll>(ask_queries_count, garlands_count, 0);
        FenwickTreeSum2D<ll> tree(n + 1, m + 1);
        for (int garland_id : range(garlands_count)) {
            for (const auto& lamp : garlands[garland_id]) {
                tree.inc(lamp.position.x, lamp.position.y, lamp.weight);
            }
            for (int ask_query_id : range(ask_queries_count)) {
                const auto& query = ask_queries[ask_query_id];
                weight_sum[ask_query_id][garland_id] = tree.query(query.first.x, query.first.y, query.second.x, query.second.y);
            }
            for (const auto& lamp : garlands[garland_id]) {
                tree.inc(lamp.position.x, lamp.position.y, -lamp.weight);
            }
        }

        std::vector<int> is_on(garlands_count, 1);
        for (const auto& query : queries) {
            if (query.type == Query::Type::Switch) {
                is_on[query.id] ^= 1;
                continue;
            }
            ll ans = 0;
            for (int garland_id : range(garlands_count)) {
                ans += weight_sum[query.id][garland_id] * is_on[garland_id];
            }
            out << ans << std::endl;
        }
	}


	EGirlyandi() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
