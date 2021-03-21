#include "base/header.hpp"
#include "collections/value_compressor.hpp"

class EMalenkiiArtyomkaIMashinaVremeni {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct Query {
	    int type;
	    int time;
	    int value;
	    int id;
	};

	struct Block {
	    int balance_ = 0;
	    std::set<pii> operations;

	    void add(const int time) {
	        ++balance_;
	        operations.emplace(pii{time, 1});
	    }

	    void del(const int time) {
	        --balance_;
	        operations.emplace(pii{time, -1});
	    }

	    int balance(const int time) const {
            if (operations.empty() || operations.begin()->first > time) {
                return 0;
            }
	        if (operations.rbegin()->first <= time) {
                return balance_;
	        }
	        int ans = 0;
	        for (const auto& it : operations) {
	            if (it.first > time) {
	                break;
	            }
	            ans += it.second;
	        }
	        return ans;
	    }
	};

	static constexpr int kBlockSize = 777;

	void solve(std::istream& in, std::ostream& out) {
	    int n;
	    in >> n;
	    std::vector<Query> queries;
	    std::vector<int> times;
        for (int i : range(n)) {
            int type, time, value;
            in >> type >> time >> value;
            queries.emplace_back(Query{type, time, value, i});
            times.emplace_back(time);
        }
        sort(queries, [](const Query& lhs, const Query& rhs) {
           return lhs.value < rhs.value || lhs.value == rhs.value && lhs.id < rhs.id;
        });

        sort(times);
        IntegralValueCompressor<int> compressed_times(times);
        for (auto& query : queries) {
            query.time = compressed_times[query.time];
        }

        std::map<int, int> answers;

        auto get_block_id = [](const int time) {
            return time / kBlockSize;
        };

	    int index = 0;
	    while (index < n) {
            std::vector<Block> blocks(kBlockSize);
	        const int cur_value = queries[index].value;
	        while (index < n && queries[index].value == cur_value) {
                const auto& query = queries[index];
                ++index;

	            const int block_id = get_block_id(query.time);
                if (query.type == 3) {
                    int ans = 0;
                    for (int i : inclusiveRange(block_id)) {
                        ans += blocks[i].balance(query.time);
                    }
                    answers.emplace(pii{query.id, ans});
                    continue;
                }
                if (query.type == 1) {
                    blocks[block_id].add(query.time);
                }
                if (query.type == 2) {
                    blocks[block_id].del(query.time);
                }
	        }
	    }

	    for (const auto& it : answers) {
	        out << it.second << std::endl;
	    }
	}


	EMalenkiiArtyomkaIMashinaVremeni() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
