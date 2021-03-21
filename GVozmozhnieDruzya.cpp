#include "base/header.hpp"
#include "collections/value_compressor.hpp"

class GVozmozhnieDruzya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;

        ValueCompressor<std::string> compressor;
        std::vector<pii> pairs;

        for (int i : range(n)) {
            std::string a, b;
            in >> a >> b;
            pairs.emplace_back(compressor[a], compressor[b]);
        }

        const int people = compressor.size();
        auto friends = make_vector<int>(people, 0, 0);
        for (const auto& pair : pairs) {
            int x, y;
            std::tie(x, y) = pair;
            friends[x].emplace_back(y);
            friends[y].emplace_back(x);
        }

        out << people << std::endl;
        for (int v : range(people)) {
            std::vector<bool> is_friend(people, false);
            std::vector<int> friends_cnt(people, 0);
            for (const int to : friends[v]) {
                is_friend[to] = true;
                for (const int potential : friends[to]) {
                    ++friends_cnt[potential];
                }
            }
            int ans = 0;
            int max = 0;
            for (int to : range(people)) {
                if (!is_friend[to] && v != to) {
                    const int cnt = friends_cnt[to];
                    if (max < cnt) {
                        ans = 1;
                        max = cnt;
                    }
                    else if (max == cnt) {
                        ++ans;
                    }
                }
            }
            out << compressor.get_by_id(v) << " " << ans << std::endl;
        }
	}


	GVozmozhnieDruzya() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
