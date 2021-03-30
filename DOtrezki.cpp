#include "base/header.hpp"

class DOtrezki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct Event {
	    int x;
	    bool close;
        int id;

        std::tuple<int, int, int> as_tuple() const {
            return std::make_tuple(x, close, id);
        }

        bool operator <(const Event& rhs) const {
            return as_tuple() < rhs.as_tuple();
        }

	};

	void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;

        std::vector<Event> events;
        for (int i : range(n)) {
            int l, r;
            in >> l >> r;
            if (l > r) {
                std::swap(l, r);
            }
            events.emplace_back(Event{l, false, i});
            events.emplace_back(Event{r, true, i});
        }
        sort(events);

        std::set<int> active;
        std::set<int> used;

        std::vector<int> ans;
        for (const auto& event : events) {
            if (!event.close) {
                active.emplace(event.id);
                continue;
            }
            if (!used.count(event.id)) {
                ans.emplace_back(event.x);
                while (!active.empty()) {
                    used.emplace(*active.begin());
                    active.erase(active.begin());
                }
            }
        }
        out << ans.size() << std::endl;
        for (int x : ans) {
            out << x << " ";
        }
        out << std::endl;
	}


	DOtrezki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
